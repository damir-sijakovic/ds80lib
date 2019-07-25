#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "../include/dslib.h"
#include "../include/vector.h"
#include "../include/linkedlist.h"
 

DSLinkedList *dsll_initilize(){    
    char *function_error = NULL;
    
    size_t adt_size = sizeof(DSLinkedList);
    DSLinkedList *t = malloc(adt_size);
    if (!t){
        fprintf(stderr, "Couldn't allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    memset(t, 0, adt_size);
    
    return t;
}


DSNode *dsll_createNode(void *data){
    assert(data != NULL);
    
    size_t adt_size = sizeof(DSNode);
    DSNode *t = malloc(adt_size);
    
    if (!t){
        fprintf(stderr, "Couldn't allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    
    t->data = data;
    t->next = NULL;
    
    return t;
}


int dsll_terminate(DSLinkedList **l){    
    DSNode *t;
    while ((t = (*l)->head) != NULL) { 
        (*l)->head = (*l)->head->next;  
        free (t);                
    }
    free(*l);
}


size_t dsll_push(DSLinkedList **l, void *data){ //add to end return new size
    assert(*l); assert(data);
        
    if ((*l)->length == 0){
        DSNode *t =  dsll_createNode(data);    
        (*l)->head = t;
        (*l)->tail = (*l)->head;
        (*l)->length = 1;
        return 1;
    }
    else {
        DSNode *t =  dsll_createNode(data);    
        (*l)->tail->next = t;
        (*l)->tail = t;
        (*l)->length++;  
        return (*l)->length;  
    }
    
    return 0;
}


void *dsll_pop(DSLinkedList **l){ //rem last pass rem data
    assert(*l);
    
    void *return_data = NULL;
    
    if ((*l)->length == 0){
        return NULL;
    }
    else if ((*l)->length == 1){
        return_data = (*l)->head->data;
        free((*l)->head);
        (*l)->head = NULL;
        (*l)->length--;  
        return return_data;
    }
    else {
        DSNode *t = (*l)->head;    
        unsigned i = 0;
        
        for (; i < (*l)->length; i++){       
            if (i+2 == (*l)->length){
                return_data = t->next->data;
                free(t->next);
                t->next = NULL;
                (*l)->length--;
                return return_data;
            }
            t = t->next;             
        }  
    }
}


size_t dsll_unshift(DSLinkedList **l, void *val){ //add first return length
    assert(*l); assert(val);
    
    DSNode *t = dsll_createNode(val);
    t->next = (*l)->head;   
    (*l)->head = t;
    (*l)->length++; 
    return (*l)->length; 
}


void *dsll_shift(DSLinkedList **l){ //rem first and return value
    assert(*l);

    void *return_data = NULL;

    if ((*l)->length == 0){
        return NULL;
    }
    else if ((*l)->length == 1){
        return_data = (*l)->head->data;
        free((*l)->head);
        (*l)->head = NULL;
        (*l)->length--;  
        return return_data;
    }
    else {
        DSNode *t = (*l)->head;
        (*l)->head = (*l)->head->next;        
        return_data = t->data;
        free(t);
        (*l)->length--; 
        return return_data; 
    }
    
}


void dsll_firstToLast(DSLinkedList **l){
    assert(*l); dsll_push(l, dsll_shift(l));    
}


void dsll_lastToFirst(DSLinkedList **l){
    assert(*l);
    dsll_unshift(l, dsll_pop(l));    
}


boolean dsll_forEach(DSLinkedList **l, boolean (*pf)(void**)){
    assert(*l); assert(pf);
    
    DSNode *t = (*l)->head;    
    boolean ret_bool = FALSE;  
    unsigned i = 0;    
    
    for (; i < (*l)->length; i++){        
        ret_bool = pf(&t->data);
        t = t->next;
    }   
    
    return ret_bool;
}

int dsll_forEachComplex(DSLinkedList **l, int (*pf)(void**, void**), void **data){ //pf returns int for more complex replies 
    assert(*l); assert(pf);
    
    DSNode *t = (*l)->head;    
    int ret_int = 0;  
    unsigned i = 0;    
    
    for (; i < (*l)->length; i++){        
        ret_int = pf(&t->data, data);
        t = t->next;
    }   
    
    return ret_int;
}

//arg 'data' gets passed in as second arg to pf, loop stops if 'data' arg is set to NULL in pf function    
void *dsll_forEachData(DSLinkedList **l, void* (*pf)(void**, void**), void **data){ 
    assert(*l); assert(pf);    
    
    DSNode *t = (*l)->head;    
    void *ret = NULL;  
    unsigned i = 0;    
    
    for (; i < (*l)->length; i++){   
        if (*data == NULL) {
            return ret;
        }         
        ret = pf(&t->data, data);
        t = t->next;
    }   
    
    return ret;
}


void *dsll_get(DSLinkedList *l, unsigned index){
    assert(l); assert(index < l->length);
    
    unsigned i = 0;    
    DSNode *t = l->head;
    for (; i < index; i++){        
        t = t->next;
    }   
    
    return t->data;     
}


void *dsll_set(DSLinkedList *l, unsigned index, void *data){ //fix bad return
    assert(l); assert(index < l->length);
    
    unsigned i = 0;    
    DSNode *t = l->head;
    for (; i < index; i++){        
        t = t->next;
    }   
    
    t->data = data; 
    return t->next; 
    
}


boolean dsll_dataExists(DSLinkedList *l, void *data){   
    assert(l); assert(data);
     
    DSNode *t = l->head;    
    unsigned i = 0;   
    
    for (; i < l->length; i++){        
        if (t->data == data){
            return TRUE;
        }
        t = t->next;
    }   
    
    return FALSE;    
}


DSLinkedList *dsll_merge(DSLinkedList *a, DSLinkedList *b){
    assert(a); assert(b);
    
    char *function_error = NULL;
    unsigned i = 0;
    DSNode *t = NULL;  
    
    DSLinkedList *r = dsll_initilize();
    r->length = a->length + b->length;
    r->head = a->head;
    
    t = a->head;
    for (; i < a->length; i++){       
        if (i+1 == a->length){
            break;
        }
        t = t->next;             
    }  
    
    t->next = b->head;

    i = 0;
    t = b->head;
    for (; i < b->length; i++){       
        if (i+1 == b->length){
            break;
        }
        t = t->next;             
    }  
    
    r->tail = t;
    
    return r;     
}


int dsll_findPrev(DSLinkedList **l, DSNode **prev, unsigned idx){ //Return code - 0: empty list, -1: no prev item, 1: found data
    assert(*l); assert(*prev); assert(idx <= (*l)->length);
    
    DSNode *t = (*l)->head; 
    unsigned i = 0;
    if ((*l)->length == 0){
        *prev = NULL;
        return 0;
    }
    
    while (t){ 
        if (i == idx-1){ 
            *prev = t;
            return 1;
        }

        t = t->next;
        i++;
    }   
    
    if (idx > i){
        *prev = NULL;
        return -1;
    }
    
}

boolean dsll_find(DSLinkedList **l, DSNode **n, unsigned idx){ 
    assert(*l); assert(*n); 
    assert(idx <= (*l)->length);
    
    
    DSNode *t = (*l)->head; 
    unsigned i = 0;
    if ((*l)->length == 0){
        *n = NULL;
        return FALSE;
    }
    
    while (t){ 
        if (i == idx){ 
            *n = t;
            return TRUE;
        }

        t = t->next;
        i++;
    }  
}



DSNode *dsll_findDataGetNode(DSLinkedList **l, void *data){    
    assert(*l); assert(data);    
    
    DSNode *t = (*l)->head;    
    unsigned i = 0;   
    
    for (; i < (*l)->length; i++){        
        if (t->data == data){
            return t;
        }
        t = t->next;
    }   
    
    return NULL;    
}


int dsll_findDataIndex(DSLinkedList **l, void *data){   
    assert(*l); assert(data);
     
    DSNode *t = (*l)->head;    
    unsigned i = 0;   

    for (; i < (*l)->length; i++){        
        if (t->data == data){
            return i;
        }
        t = t->next;
    }   
    
    return -1;    
}


int dsll_findPrevData(DSLinkedList **l, DSNode **prev, void *data){ //Return code - 0: empty list, -1: no prev item, 1: found data
    assert(*l); assert(*prev); assert(data);
           
    DSNode *t = (*l)->head; 
    DSNode *p = NULL; 
    unsigned i = 0;
    if ((*l)->length == 0 ){
        *prev = NULL;
        return 0; //empty list
    }
    
    for (; i < (*l)->length; i++){        
        if (t->data == data){
            if (i == 0){
                *prev = NULL;
                return -1; //no prev item
            }
            
            *prev = p;
            return 1; //success
        }
        p = t;
        t = t->next;      
    } 
}


boolean dsll_swap(DSLinkedList *l, unsigned idx_a, unsigned idx_b){
    assert(l); assert(idx_a < l->length);
    assert(l); assert(idx_b < l->length);
        
    DSNode *a = NULL;
    DSNode *b = NULL;
    void *data = NULL;
    //if (dsll_find(&l, &a, idx_a) && dsll_find(&l, &b, idx_b)){
    if (dsll_find(&l, &a, idx_a) && dsll_find(&l, &b, idx_b)){
        data = a->data;
        a->data = b->data;
        b->data = data;
        return TRUE;
    }
    else{
        return FALSE;
    }
    
    
}

/* dsvector */

DSLinkedList *dsll_vectorToLinkedList(DSVector *v){
    assert(v != NULL);
    
    if (v->length == 0){
        return NULL;
    }
    
    DSLinkedList *t = dsll_initilize();
    unsigned i = 0;
    for(; i<v->length; i++){
        dsll_push(&t, v->data[i]);
    }
    
    return t;
}


DSVector *dsll_linkedListToVector(DSLinkedList *l){
    assert(l != NULL);
    
    DSVector *v = dsv_create(l->length, DS_VECTOR_MODE_STEP, 1); 
    DSNode *t = l->head; 
    unsigned i = 0;
    
    for (; i<l->length; i++){
        dsv_set(&v, i, t->data); 
        //dsv_push(&v, t->data); //push adds after v->length
        t = t->next; 
    }
    
    return v;
}


DSLinkedList *dsll_reverse(DSLinkedList *l){ 
    assert(l != NULL);
        
    DSVector *v = dsll_linkedListToVector(l); //ahhhh reuse
    dsv_reverse(&v); 
    DSLinkedList *r = dsll_vectorToLinkedList(v);
    
    return r;   
}
 
 

