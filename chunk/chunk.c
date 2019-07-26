#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "../include/dslib.h"
#include "../include/chunk.h"

DSChunk *dsch_new(size_t size){ 
    assert(size>1);

    size_t malloc_size = (sizeof(DSChunk) - sizeof(unsigned char)) + size; 
    DSChunk *t = malloc(malloc_size);
    if (!t){
        printf("%s\n", "Memory allocation error!");
        abort();
    }
    
    memset(t, 0, malloc_size);
    t->size = size;
    
    return t;
}


void dsch_set(DSChunk **handle, void *data){
    assert (*handle != NULL);    
    memcpy((*handle)->data, data, (*handle)->size);  
    return;
}



DSChunk *dsch_newStr(char *str){
    assert (str != NULL);
    
    size_t copysize = 0;
    size_t strsize = 0;
    
    strsize = strlen(str);
    copysize = (strsize > DS_CHK_NEWSTR_LIMIT) ? DS_CHK_NEWSTR_LIMIT : strsize;
        
    DSChunk *t = dsch_new(copysize+1);


    t->size = copysize;
    memcpy(t->data, str, copysize);  
    return t;
}



DSChunk *dsch_newText(char *str, size_t limit){
    assert (str != NULL);
    assert (limit > 0);

    DSChunk *t = dsch_new(limit+1);
    
    t->size = limit;
    memcpy(t->data, str, limit);  
    return t;
}


void *dsch_get(DSChunk *handle){
    assert (handle != NULL);
    return handle->data;
}

void dsch_nullify(DSChunk **handle){
    assert (*handle != NULL);    
    memset((*handle)->data, 0, (*handle)->size);
}
   
void dsch_copy(DSChunk *source, DSChunk **destination){
    assert(source != NULL);    
    assert(*destination != NULL);    
    
    memcpy((*destination)->data, source->data, (*destination)->size); 
}



void dsch_resize(DSChunk **handle, size_t size){
    assert(*handle != NULL);    
    assert(size > 0);

    DSChunk *t = dsch_new(size);    
    dsch_copy(*handle, &t);
    free(*handle);
    *handle = t;    
}



DSChunk *dsch_join(DSChunk *a, DSChunk *b){
    assert(a != NULL);   
    assert(b != NULL);   
    size_t return_obj_size = 0;
    
    return_obj_size = a->size + b->size;

    DSChunk *t = dsch_new(return_obj_size);

    t->size = return_obj_size;
    memcpy(&t->data[0], a->data, a->size);
    memcpy(&t->data[a->size], b->data, b->size);
    
    return t;    
}



void dsch_destroy(DSChunk **handle){
    assert(*handle != NULL);   
    free(*handle);
    *handle = NULL;
}



DSChunk *dsch_split(DSChunk **original, size_t idx){
    assert((*original) != NULL);   
    assert(idx > 1);
    assert(idx < (*original)->size);
    
    size_t passback_size = (*original)->size - idx;   
    DSChunk *t = dsch_new(passback_size);
    
    dsch_set(&t, &(*original)->data[idx]);
    dsch_resize(original, idx);    
    return t;
}
 

 
 
void dsch_removeRange(DSChunk **handle, size_t idx, size_t size){  
    assert((*handle) != NULL);   
    assert(size > 1);
    assert(idx <= (*handle)->size);
        
        
    size_t t_size = (*handle)->size - size;

    DSChunk *t = dsch_new( t_size);
      
    memcpy(t->data, (*handle)->data, idx);
    memcpy(&t->data[idx], &(*handle)->data[idx+size], t_size-idx);
    
    free(*handle);
    *handle = t;  
}


 
void dsch_ltrim(DSChunk **handle, size_t size){  
    assert((*handle) != NULL);  
    assert (size < (*handle)->size);

    size_t t_size = (*handle)->size - size;
    DSChunk *t = dsch_new( t_size);
        
    memcpy(t->data, &(*handle)->data[size], (*handle)->size - size);
    free(*handle);
    *handle = t;    
}


void dsch_rtrim(DSChunk **handle, size_t size){
    assert((*handle) != NULL);  
    assert (size < (*handle)->size);  
    
    size_t t_size = (*handle)->size - size;

    DSChunk *t = dsch_new( t_size);

    memcpy(t->data, (*handle)->data, (*handle)->size - size);
    free(*handle);
    *handle = t;   
}

void dsch_save(DSChunk *h, char *file){        
    assert(h != NULL);
    assert(file != NULL);
    
    FILE *iofile;
    
    if ((iofile = fopen(file, "wb")) == NULL){
        fprintf(stderr, "Could not open %s for output.\n", file);
        exit(1);
    }
    
    size_t chunk_size = sizeof (h) + h->size;
    fwrite(h, chunk_size, 1, iofile);    
    fclose(iofile);
}

DSChunk *dsch_load(char *file){   
    assert(file != NULL);
    
    FILE *iofile;
    
    if ((iofile = fopen(file, "rb")) == NULL){
        fprintf(stderr, "Could not open %s for output.\n", file);
        exit(1);
    }
    
    DSChunk header;
    fread(&header, sizeof (DSChunk), 1, iofile);   
    
    DSChunk *t = dsch_new(header.size); 
    rewind(iofile);

    fread(t, sizeof (DSChunk) + header.size, 1, iofile);
    
    fclose(iofile);    
    return t;
}

void dsch_iterate(DSChunk **h, unsigned char *(* f)( unsigned char*) ){
    unsigned int i = 0;
    for (; i<(*h)->size; i++){
        f(&(*h)->data[i]);
    }    
}

void dsch_iterBlocks(DSChunk **h, unsigned int block_size, void (*func)(void*)){
    size_t data_size = (*h)->size;
    
    char *buffer = malloc(block_size+1);
    memset(buffer, '\0', block_size+1);
    
    char *data_end = &(*h)->data[data_size];
    char* current = (*h)->data;
    while (current < data_end){
        memcpy(buffer, current, block_size);        
        //printf("%s\n", buffer);
        func(buffer);
        
        current += block_size;
    }
    
    free(buffer);
}


void *dsch_find(DSChunk *haystack, DSChunk *needle){   
    assert(haystack != NULL);
    assert(needle != NULL);
    
    unsigned char *needle_data = needle->data;
    unsigned char *haystack_data = haystack->data;
    size_t haystack_size = haystack->size;
    size_t needle_size = needle->size;
    
    unsigned i = 0;
    unsigned j = 0;
    unsigned break_loop = 0;
    void *match_addrs = NULL;    
    
    for (; i<haystack_size; i++){
        if (break_loop) break;        

        if ((i+needle_size) > haystack_size){
            match_addrs = 0;
            break;
        }   
        
        if (haystack_data[i] == needle_data [0]){
            match_addrs = &haystack_data[i];
            
            for (; j<needle_size; j++){
                if (haystack_data[i+j] != needle_data[j]){
                    match_addrs = NULL;
                    j = 0;
                    break;
                }   

                if (j == (needle_size-1)){
                    i = i+j;
                    break_loop = 1;
                    break;
                }
            }
        }
    }
    
    return match_addrs;
}

boolean dsch_allowBytes(DSChunk *c, DSChunk *pattern){
    assert(c == NULL);
    assert(pattern == NULL);
    
    boolean iter_test = FALSE;
    unsigned i = 0;
    unsigned j = 0;
    for (; i<c->size; i++, j=0){
        for (; j<pattern->size; j++){
            if (c->data[i] == pattern->data[j]) iter_test = TRUE; 
        }        
        if (!iter_test) break;        
        iter_test = (i+1 == c->size) ? TRUE : FALSE;
    }    
    
    return iter_test;
}


