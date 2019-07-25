#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "../include/dslib.h"
#include "../include/vector.h"

/****************************************************************************\
 HELPERS
\****************************************************************************/

size_t dsv_malloc_calc(size_t base_size, size_t item_size, size_t item_num){
    assert(base_size > 0); assert(item_size > 0); assert(item_num >= 0); 
    assert(base_size > item_size);
    
    int ret_size = 0;
    
    if (item_num == 0)
        return base_size - item_size;
    else if (item_num > 0)
        ret_size = (base_size - item_size) + (item_size * item_num);
    
    return ret_size;
}


unsigned dsv_double_calc(unsigned amount){
    assert(amount > 0);
    
    int running = 1;
    int i = 1;
    
    while (running){
        if (i>amount-1){break;}        
        i = (i==1) ? 2 : i+i; 
    }    
        
    return i;
}


unsigned dsv_step_calc(unsigned amount, unsigned step){
    assert(amount > 0); assert(step > 0);
    
    unsigned i=0;
    unsigned j=0;
    for (; j<(amount); i++){
        j += step;
    }
    
    return j;
}

/****************************************************************************\
 INTERFACE
\****************************************************************************/

DSVector *dsv_create(size_t size, DSVectorMode mode, int step){
    //assert(size > 0);    
    assert(size < DS_VECTOR_ITEM_LIMIT);
    if (mode == DS_VECTOR_MODE_STEP) assert(step > 0);
    
    size_t malloc_size = dsv_malloc_calc(sizeof (DSVector), sizeof(void *), size);
    DSVector *t = malloc(malloc_size);
    if (!t){
        printf("%s\n", "Memory allocation error!");
        abort();
    }
    memset(t, 0, malloc_size);
    t->length = size;
    t->mode = mode;
    t->step = step;
    
    /*
    int i = 0;
    for (;i<t->length; i++){
        t->data[i] = NULL;
    }
    */
    
    return t;
}


void dsv_destroy(DSVector *handle){
    assert(handle);
    free(handle);
}


int dsv_resize(DSVector **handle, size_t length){
    assert(*handle); // assert(length > 0); 
    
#ifdef DS_VECTOR_DEBUG_RESIZE
    printf("Debug: Resize to: %d \n", length);
#endif
    
    size_t old_length = (*handle)->length;    
    size_t malloc_size = dsv_malloc_calc(sizeof (DSVector), sizeof(void *), length);
    size_t old_malloc_size = dsv_malloc_calc(sizeof (DSVector), sizeof(void *), old_length);
    DSVector *t = dsv_create(length, (*handle)->mode, (*handle)->step);
        
    if (old_malloc_size < malloc_size){
        memcpy(t, *handle, old_malloc_size);
    }
    
    if (old_malloc_size > malloc_size){
        memcpy(t, *handle, malloc_size);
    }
        
    t->length = length;
    
    DSVector *f = *handle;
    *handle = t;
    free(f);
}

DSVector *dsv_clone(DSVector *handle){
    assert(handle != NULL);
    
    size_t malloc_size = dsv_malloc_calc(sizeof (DSVector), sizeof(void *), handle->length);
    DSVector *t = malloc(malloc_size);
    memcpy(t, handle, malloc_size);
    
    return t;
}


boolean dsv_set(DSVector **handle, unsigned index, void *data){  
    assert(*handle); assert(index < DS_VECTOR_ITEM_LIMIT); 
    
    DSVectorMode mode = (*handle)->mode;
 
    if (index >= (*handle)->length){
        if (mode == DS_VECTOR_MODE_DOUBLE){
            dsv_resize(handle, dsv_double_calc(index+1));          
        }         
        if (mode == DS_VECTOR_MODE_STEP){
            dsv_resize(handle, dsv_step_calc(index+1, (*handle)->step));          
        }         
    }
    
    (*handle)->data[index] = data;
}


void *dsv_get(DSVector *handle, unsigned index){  
    assert(handle); assert(index < handle->length); assert(index < DS_VECTOR_ITEM_LIMIT); 
    
    return handle->data[index];
}


void **dsv_getContainer(DSVector **handle, unsigned index){  
    assert(*handle); assert(index < DS_VECTOR_ITEM_LIMIT); 
    
    return &((*handle)->data[index]);
}


int dsv_shrinkToFit(DSVector **handle){
    assert(*handle);
    
    if ((*handle)->data[(*handle)->length-1] == NULL){
        int j = 0;
        int i = (*handle)->length-1;
        for (; (*handle)->data[i] == NULL; --i, j++);
        dsv_resize(handle, (*handle)->length - j);
        return j;
    }
    return -1;    
}


boolean dsv_forEach(DSVector **handle, boolean (*fn_ptr)(void **)){
    assert(*handle); assert(fn_ptr);
    boolean ret = TRUE;   
    unsigned i = 0;   
    for (; i<(*handle)->length; i++){
        if (ret){
            ret = fn_ptr(&(*handle)->data[i]);
        }
        else {
            return FALSE;
        }
    }
    
    return ret;    
}

//pf returns int for more complex replies    
int dsv_forEachComplex(DSVector **handle, int (*fn_ptr)(void**, void**), void **data){ 
    assert(*handle); assert(fn_ptr);
    
    int ret = 0;   
    unsigned i = 0;   
    for (; i<(*handle)->length; i++){
        if (*data == NULL) {
            return ret;
        } 
        ret = fn_ptr(&(*handle)->data[i], data);
    }
    
    return ret; 
}



//arg 'data' gets passed in as second arg to pf, loop stops if 'data' arg is set to NULL in pf function 
void *dsv_forEachData(DSVector **handle, void *(*fn_ptr)(void**, void**), void **data){
    assert(*handle); assert(fn_ptr);
    
    void *ret = 0;   
    unsigned i = 0;   
    for (; i<(*handle)->length; i++){
         if (*data == NULL) {
            return ret;
        } 
        ret = fn_ptr(&(*handle)->data[i], data);
    }
    
    return ret; 
}




int dsv_push(DSVector **handle, void *data){
    assert(*handle); assert(data);
    assert((*handle)->mode == DS_VECTOR_MODE_STEP);
    assert((*handle)->step == 1);
    
    unsigned amount = (*handle)->length;
    dsv_set(handle, amount, data);    
    return (*handle)->length;  
}

void *dsv_pop(DSVector **handle){
    assert(*handle); 
    assert((*handle)->mode == DS_VECTOR_MODE_STEP);
    assert((*handle)->step == 1);
    
    if ((*handle)->length == 0) return NULL;
    
    void *t = (*handle)->data[(*handle)->length-1];
    dsv_resize(handle, (*handle)->length - 1);
    
    return t;
}

int dsv_unshift(DSVector **handle, void *data){
    assert(*handle); 
    assert((*handle)->mode == DS_VECTOR_MODE_STEP);
    assert((*handle)->step == 1);
    
    if ((*handle)->length == 0){
        return dsv_push(handle, data);
    }
    
    int old_size = (*handle)->length;    
    dsv_resize(handle, (*handle)->length+1);   
        
    int i = (*handle)->length-2;        
    for (; i>-1; i--){
        (*handle)->data[i+1] = (*handle)->data[i];
    }        
    (*handle)->data[0] = data;
    
    return (*handle)->length;
}

void *dsv_shift(DSVector **handle){
    assert(*handle); 
    assert((*handle)->mode == DS_VECTOR_MODE_STEP);
    assert((*handle)->step == 1);
    
    if ((*handle)->length == 0) return NULL;
    
    void *t = (*handle)->data[0];
    
    unsigned i = 1; 
    for (; i<(*handle)->length; i++){
        (*handle)->data[i-1] = (*handle)->data[i];
    }
    
    dsv_resize(handle, (*handle)->length-1); 
    
    return t;
}

size_t dsv_getByteSize(DSVector *v){
    assert(v != NULL); 
      
    size_t r = 0;    
    r = sizeof(DSVector) - sizeof(void*);
    
    if (v->length > 0){
        r += sizeof(void*) * v->length;
    }
    else {
        r += sizeof(void*);
    }
    
    return r;
}


void dsv_nullify(DSVector **v){
    assert(*v != NULL);    
    memset(*v, 0, dsv_getByteSize(*v));
}

void dsv_nullifyMembers(DSVector **handle){
    assert(*handle != NULL);    
    int i = 0;
    
    if ((*handle)->length == 0) return;
    
    for (; i<(*handle)->length; i++){
        (*handle)->data[i] = NULL; 
    }
    
}

boolean dsv_reverse(DSVector **v){
    assert(*v != NULL);
    
    void *t = NULL;    
    unsigned i = 0;
    unsigned j = 0;
    unsigned break_loop_at = 0;
    j = (*v)->length - 1;  
    
    if ((*v)->length == 1) return FALSE;
           
    break_loop_at = DS_ISEVEN((*v)->length) ? 1 : 2;
    for (; i<(*v)->length; i++, j--){ 
        if (i==j-break_loop_at){
            t = (*v)->data[i];
            (*v)->data[i] = (*v)->data[j];
            (*v)->data[j] = t;
            break;            
        }
        t = (*v)->data[i];
        (*v)->data[i] = (*v)->data[j];
        (*v)->data[j] = t;
    }
        
    return TRUE;
}


boolean dsv_compare(DSVector *a, DSVector *b){
    assert(a); assert(b);
    
    boolean not_eq = FALSE;
    boolean mode_pass = TRUE;
    boolean r = FALSE;
            
    mode_pass = (a->mode != b->mode) ? FALSE : TRUE;
      
    if (mode_pass){
        unsigned i = 0;
        for (; i<a->length; i++){
            if (a->data[i] != b->data[i]){
                not_eq = TRUE;
                break;
            }
        }        
        r = not_eq ? FALSE : TRUE;
    }

    return r;
}


int dsv_areMembers(DSVector *handle, void *data, unsigned idx){ 
    assert(handle);
    assert(idx < (handle)->length);
    assert(data);     

    unsigned i = idx;   
    for (; i<handle->length; i++){
        if (handle->data[i] == data){
            return i;
        }
    }
    return -1;
}

void *dsv_removeMember(DSVector **handle, unsigned idx){ 
    assert(*handle); assert(idx < (*handle)->length);
    
    if (idx == 0){
        return dsv_shift(handle);
    }
    if (idx == (*handle)->length-1){
        return dsv_pop(handle);
    }
        
    void *t = (*handle)->data[idx];
    unsigned i = idx+1;     
    for (; i<(*handle)->length; i++){
        (*handle)->data[i-1] = (*handle)->data[i];
    }
    
    dsv_resize(handle, (*handle)->length-1); 
    return t;
}

int dsv_insertMember(DSVector **handle, unsigned idx, void *data){
    assert(*handle); assert(idx < (*handle)->length); assert(data);
    
    if (idx == 0){
        return dsv_unshift(handle, data);
    }
    if (idx == (*handle)->length-1){
        return dsv_push(handle, data);
    }
     
    int i = (*handle)->length-1;     
    dsv_resize(handle, (*handle)->length+1);
    
    for (; i>idx-1; i--){
        (*handle)->data[i+1] = (*handle)->data[i];
    }  
    
    (*handle)->data[idx] = data;    
    return (*handle)->length;
       
}

void dsv_swapMembers(DSVector **handle, unsigned idx_a, unsigned idx_b){
    assert(*handle != NULL); assert(idx_a < (*handle)->length); assert(idx_b < (*handle)->length);

    if (idx_a == idx_b) return;

    void *t = NULL;
    t = (*handle)->data[idx_a];
    (*handle)->data[idx_a] = (*handle)->data[idx_b];
    (*handle)->data[idx_b] = t;
}

//this is lazy copy/paste of dsll_firstToLast, todo: rebuild with 'for' loop 
void dsv_firstToLast(DSVector **handle){
    assert(*handle);
    dsv_push(handle, dsv_shift(handle));
}
//as above
void dsv_lastToFirst(DSVector **handle){
    assert(*handle);
    dsv_unshift(handle, dsv_pop(handle));  
}



DSVector *dsv_merge(DSVector *a, DSVector *b){ 
    assert(a); assert(b);
    
    if (a->length && !b->length) return a;
    if (b->length && !a->length) return b;
    
    size_t length = a->length + b->length;    
    if (length == 0) return NULL;  
    
    size_t malloc_size = dsv_malloc_calc(sizeof (DSVector), sizeof(void *), length);
    DSVector *t = dsv_create(length, DS_VECTOR_MODE_STEP, 1);    
    
    unsigned i = 0;
    unsigned j = 0;
    for (; i<a->length; i++){
        t->data[i] = a->data[i];
    }
    for (; j<b->length; j++, i++){
        t->data[i] = b->data[j];
    }
    
    return t;
}


boolean dsv_isNull(DSVector *handle, unsigned idx){
    assert(handle); assert(idx < handle->length);
    
    if (handle->data[idx] == NULL){
        return TRUE;
    }
    
    return FALSE;
}


int dsv_countUsed(DSVector *handle){
    assert(handle);
    
    unsigned count = 0;
    unsigned i = 0;
    for (;i<handle->length; i++){
        if (handle->data[i] != NULL){
            count++;
        }
    }

    return count;
}

int dsv_countFree(DSVector *handle){
    assert(handle);
    
    unsigned count = 0;
    unsigned i = 0;
    for (;i<handle->length; i++){
        if (handle->data[i] == NULL){
            count++;
        }
    }

    return count;
}

