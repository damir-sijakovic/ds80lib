#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "../include/dslib.h"
#include "../include/pair.h"
#include "../include/vector.h"
#include "../include/linkedlist.h"
#include "../include/hashtable.h"

/*
 
typedef struct DSHashTable{
    unsigned size;    
    DSHashTableEnum hash;
    DSHashTableModeEnum bucket_mode;
    DSVector *table;
} DSHashTable;

typedef struct DSHashTablePair {    
    char *key;
    void *data;
} DSHashTablePair;

 */



static float dshs_toPrime_sqrt(float number){
    int i;
    float x,y;
    x = number * 0.5;
    y = number;
    i = * (int *) &y;
    i = 0x5f3759df - (i >> 1);
    y = * (float *) &i;
    y = y * (1.5 - (x * y * y));
    y = y * (1.5 - (x * y * y));
    return number * y;
}

static int dshs_toPrime_check(int num){
    int i = 2, lim = (int) dshs_toPrime_sqrt(num);

    for (; i <= lim; i += 1) {
        if (num % i == 0) break;
    }
    if (i <= lim){
        return (1);
    }
    return (0);
}

int dshs_toPrime(int num){ 
    int prime = num;
    int i = 1;
    if (dshs_toPrime_check(prime) == 0) return (prime);
    while (1) {
        prime = num - i;
        if (dshs_toPrime_check(prime) == 0) break;
        prime = num + i;
        if (dshs_toPrime_check(prime) == 0) break;
        i += 1;
    }
    return (prime);
}



//forEach helper functions
static int dshs_FE_replace_hfunc(void **v, void **data){    

    DSHashTablePair *new_pair =  *data;
    DSHashTablePair *stored_pair = *v;
   
    if (new_pair->key == stored_pair->key){        
        stored_pair->data = new_pair->data;
        return 1;
    }
   
   return -1;

}


static void *dshs_FE_find_hfunc(void **v, void **data){    
    DSHashTablePair *stored_pair = *v;   
     
    if (0 == strncmp(stored_pair->key, (char*)*data, DS_HASHTABLE_KEYSTR_LIMIT)){       
        *data = NULL; //stops loop
        return stored_pair->data;
    }

   return NULL;
}

//algorithms, get more 
static unsigned dshs_algorithm_ramaKrishna(char *str, size_t size){        
    unsigned  h = 0;  
    unsigned i = 0;

    for(; i<strlen(str); ++i) {
        h ^= (h << 5) + (h >> 2) + str[i];
    }        

    return h % size;  
}


static unsigned dshs_algorithm_djb2(char *str, size_t size){        
    unsigned long hash = 5381;
    int c;

    while (c = *str++){
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % size;  
}


static unsigned dshs_algorithm_sdbm(char *str, size_t size){        
    unsigned long hash = 0;
    int c;

    while (c = *str++){
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    
    return hash % size;  
}


static unsigned dshs_algorithm_fnv32(char *str, size_t size){
    unsigned hash = DSHS_FNV_OFFSET_32, i;
    
    for (i = 0; i < strlen(str); i++) {
        hash = hash ^ (str[i]); 
        hash = hash * DSHS_FNV_PRIME_32; 
    }
    
    return hash % size;
} 


static unsigned dshs_getHash(DSHashTableEnum algorithm, char *str, size_t size){
    assert(str);
    
    if (algorithm == DSH_RAMAKRISHNA){
        return dshs_algorithm_ramaKrishna(str, size);
    }
    if (algorithm == DSH_DJB2){
        return dshs_algorithm_djb2(str, size);
    }
    if (algorithm == DSH_SDBM){
        return dshs_algorithm_sdbm(str, size);
    }
    if (algorithm == DSH_FNV32){
        return dshs_algorithm_fnv32(str, size);
    }
    
    
}


boolean dshs_isEmpty(DSHashTable *handle){ 
    assert(handle);
    
    DSVector *v = handle->table;
    boolean ret = FALSE;
    
    int i = 0;
    for (; i<v->length; i++){
        if (v->data[i] != NULL){
            ret = TRUE;
            break;
        }
    }
    
    return ret;
}


int dshs_countMembers(DSHashTable *handle){ 
    DSVector *v = handle->table;
    
    int count = 0;
    
    int i = 0;
    for (; i<v->length; i++){
        if (v->data[i] != NULL){
            if (handle->bucket_mode == DSHM_LINKEDLIST){
                DSLinkedList *t = v->data[i];
                if (t->length > 1){
                    count += t->length;
                }
                if (t->length == 1){
                    count ++;
                }
            }
            if (handle->bucket_mode == DSHM_VECTOR){
                DSVector *t = v->data[i];
                if (t->length > 1){
                     count += t->length;
                }
                if (t->length == 1){
                    count ++;
                }
            }            
        }
    }
    
    return count;
}

int dshs_countCollides(DSHashTable *handle){ 
    DSVector *v = handle->table;
    
    int count = 0;
    
    int i = 0;
    for (; i<v->length; i++){
        if (v->data[i] != NULL){
            if (handle->bucket_mode == DSHM_LINKEDLIST){
                DSLinkedList *t = v->data[i];
                if (t->length > 1){                    
                    count++;
                }
            }
            if (handle->bucket_mode == DSHM_VECTOR){
                DSVector *t = v->data[i];
                if (t->length > 1){
                     count++;
                }
            }            
        }
    }
    
    return count;
}

DSVector *dshs_convertToVector(DSHashTable *handle){
    assert(handle);
        
    int number_of_members = dshs_countMembers(handle);    
    if (number_of_members < 1){
        return NULL;
    }
    
    DSVector *v = handle->table;   
    DSVector *ret = dsv_create(number_of_members, DS_VECTOR_MODE_STEP, 1); 
    
    int pen_i = 0;
    
    int i = 0;
    for (; i<v->length; i++){
        if (v->data[i] != NULL){
            
            if (handle->bucket_mode == DSHM_LINKEDLIST){                
                DSLinkedList *base = v->data[i];
                DSNode* t = base->head;
                int j = 0;
                if (base->length > 1){
                   // printf("BASE LEN %d\n", base->length );
                   // count += t->length;                    
                    for (; j < base->length; j++){   
                        DSHashTablePair *stored_pair = t->data;                        
                        //printf("index [%d] key: %s\n", pen_i, stored_pair->key); //DEBUG    
                        dsv_set(&ret, pen_i, t->data);                        
                        t = t->next;
                        pen_i++;
                    }   
                }
                if (base->length == 1){
                    //count ++;                     
                    DSHashTablePair *stored_pair = t->data;
                    //printf("index [%d] key: %s\n", pen_i, stored_pair->key);
                    dsv_set(&ret, pen_i, t->data);  
                    
                    pen_i++;
                }
            }
            
            if (handle->bucket_mode == DSHM_VECTOR){
                DSVector *t = v->data[i];
                int j = 0;
                if (t->length > 1){
                     //count += t->length;
                     for (; j < t->length; j++){  
                         //printf("%s\n", "HI!");
                         DSHashTablePair *stored_pair = t->data[j]; 
                         //printf("index [%d] key: %s\n", pen_i, stored_pair->key);
                         dsv_set(&ret, pen_i,  t->data[j]);  
                        pen_i++;
                    }   
                }
                if (t->length == 1){
                    DSHashTablePair *stored_pair = t->data[0]; 
                    //printf("index [%d] key: %s\n", pen_i, stored_pair->key);
                    //count ++;
                    dsv_set(&ret, pen_i, t->data[0]);   
                    pen_i++;
                }
            }                        
        }
    }     
    
    return ret;
}

DSLinkedList *dshs_convertToLinkedList(DSHashTable *handle){
    assert(handle);
    DSVector *t = dshs_convertToVector(handle);
    DSLinkedList *ret = dsll_vectorToLinkedList(t);
    dsv_destroy(t);
    return ret;
}

//init function
DSHashTable *dshs_create(unsigned size, DSHashTableEnum hash, DSHashTableModeEnum mode){   
    assert(DS_ISBETWEEN(size, DS_HASHTABLE_TABLE_LOWER_LIMIT, DS_HASHTABLE_TABLE_UPPER_LIMIT));
          
    DSHashTable *t = malloc(sizeof (DSHashTable));

    t->size = size;
    t->hash = hash;
    t->bucket_mode = mode;
             
    t->table = dsv_create(size, DS_VECTOR_MODE_STEP, 1);

    return t;    
}

//set
int dshs_set(DSHashTable **handle, char *key, void *data){    
    assert(*handle); assert(key);
    
#ifdef DS_HS_SIMULATE_COLLIDE
    unsigned hash_index = (*handle)->size-1;
#else
    unsigned hash_index = dshs_getHash((*handle)->hash, key, (*handle)->size);
#endif
    
    //printf("hash_index: %d\n", hash_index );
    
    //is target slot free
    boolean slot_free = dsv_isNull((*handle)->table, hash_index);
    
    //make pair
    DSHashTablePair *pair = malloc(sizeof(DSHashTablePair));
    memset(pair, 0, sizeof(DSHashTablePair));
    pair->key = key;
    pair->data = data;    

    //get container that is holding llist
    void **data_address = dsv_getContainer(&(*handle)->table, hash_index);
    
    //is bucket linkedlist ? 
    if ((*handle)->bucket_mode == DSHM_LINKEDLIST){    
        //if slot is free init llist and push pair data
        if (slot_free){ 
            *data_address = dsll_initilize();
            dsll_push((DSLinkedList **) data_address, pair);
        }
        else {
            //look for key name in pairs and if key exist update data
            int retcode = dsll_forEachComplex((DSLinkedList **) data_address, dshs_FE_replace_hfunc, (void**)&pair);                   
            if (retcode == -1){
                dsll_push((DSLinkedList **) data_address, pair); 
            } 
            else {
                free(pair);
            }     
        }
    }
    
    
    //is bucket vector ? 
    if ((*handle)->bucket_mode == DSHM_VECTOR){
        if (slot_free){ 
            *data_address = dsv_create(0, DS_VECTOR_MODE_STEP, 1); //first arg (size) must init with 0
            dsv_push((DSVector **) data_address, pair);
        }
        else {
            //look for key name in pairs and if key exist update data
                int retcode = dsv_forEachComplex((DSVector **) data_address, dshs_FE_replace_hfunc, (void**)&pair);        
                if (retcode == -1) {
                    dsv_push((DSVector **) data_address, pair);
                } 
                else {
                    free(pair);
                }
        }   
    }   
   
    
    //return index 
    return hash_index;
}

//get
void *dshs_get(DSHashTable **handle, char *key){
    assert(*handle); assert(key);
    
    #ifdef DS_HS_SIMULATE_COLLIDE
        unsigned hash_index = (*handle)->size-1;
    #else
        unsigned hash_index = dshs_getHash((*handle)->hash, key, (*handle)->size);
    #endif
    
    void **data_address = dsv_getContainer(&(*handle)->table, hash_index);       
    
    if (*data_address == NULL){        
        return NULL;
    }
        
    //void *dsll_forEachData(DSLinkedList **l, void* (*pf)(void**, void**), void **data);
    if ((*handle)->bucket_mode == DSHM_LINKEDLIST){    
        return dsll_forEachData((DSLinkedList **) data_address, dshs_FE_find_hfunc, (void**) &key);    
    }
    
    if ((*handle)->bucket_mode == DSHM_VECTOR){
        return dsv_forEachData((DSVector **) data_address, dshs_FE_find_hfunc, (void**) &key); 
    }
    
}

boolean dshs_destroy_hfunc(void **a){
    if ((*a) != NULL){
        free(*a);
    }
    return TRUE;
}

int dshs_destroy(DSHashTable **handle){
    assert(*handle);
        
    int number_of_members = dshs_countMembers(*handle);    
    if (number_of_members < 1){
        return -1;
    }
    
    DSVector *v = (*handle)->table;  
    int pen_i = 0;
    
    int i = 0;
    for (; i<v->length; i++){
        if (v->data[i] != NULL){
            
            if ((*handle)->bucket_mode == DSHM_LINKEDLIST){                
                DSLinkedList *t = v->data[i];
                dsll_forEach(&t, dshs_destroy_hfunc);
                dsll_terminate(&t);
            }
            
            if ((*handle)->bucket_mode == DSHM_VECTOR){                
                DSVector *t = v->data[i];
                dsv_forEach(&t, dshs_destroy_hfunc);
                dsv_destroy(t);
            }                        
        }
    }     
    
    dsv_destroy(v);    
    free(*handle);
    
    
    return 0;
}
