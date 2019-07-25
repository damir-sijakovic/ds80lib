#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "../include/dslib.h"
#include "../include/pair.h"
#include "../include/vector.h"
#include "../include/linkedlist.h"
#include "../include/hashtable.h"

char *ds_mkString(char *a){
    size_t size = strlen(a);
    char *t = malloc(size+1);
    t[size] = '\0';
    memcpy(t, a, size);
    return t;
}

// vector/linkedlist forEach helper
boolean ds_printPairs_hfunc(void **a){
    if ((*a) != NULL){
        DSHashTablePair *new_pair = *a;
        printf("  key: %s, value: %s \n", new_pair->key, new_pair->data);
    }
    return TRUE;
}


int main(){
    printf("%s\n", "START test in collide vector mode with fnv32 hash algoritam.");

    //convert table size to prime number
    unsigned table_size = dshs_toPrime(8);
    
    //init datatype, DSH_FNV32 hash algoritam, DSHM_VECTOR for collide mode
    DSHashTable *hs = dshs_create(table_size, DSH_FNV32, DSHM_VECTOR);
       
    //set data
    dshs_set(&hs, "test_key_one", "HELLOWORLD1");
    dshs_set(&hs, "test_key_two", "HELLOWORLD2");
    dshs_set(&hs, "test_key_three", "HELLOWORLD3");
    dshs_set(&hs, "test_key_four", "HELLOWORLD4");
    dshs_set(&hs, "test_key_five", "HELLOWORLD5");
    dshs_set(&hs, "test_key_six", "HELLOWORLD6");
    
    //convert to vector and print members, TODO: write dshs_forEach()
    printf("\n%s\n", "Print members: ");
    DSVector *collect_vec = dshs_convertToVector(hs);
    dsv_forEach(&collect_vec, ds_printPairs_hfunc);
    printf("%s\n\n", "End Print members. ");
    dsv_destroy(collect_vec);
    
    //get data with key 'test_key_four'
    printf(" dshs_get(&hs, test_key_four): %s\n", dshs_get(&hs, "test_key_four"));    
    
    //check collides/members size
    printf(" dshs_countCollides: %d\n", dshs_countCollides(hs));
    printf(" dshs_countMembers: %d\n", dshs_countMembers(hs) );
    
    //overwrite data
    dshs_set(&hs, "test_key_four", "dshs_set_new_data_here");    
    printf(" overwrite dshs_get(&hs, test_key_four): %s\n", dshs_get(&hs, "test_key_four"));  
        
    
    //garbage collect
    dshs_destroy(&hs);
    
    printf("\n%s\n", "END test in collide vector mode with fnv32 hash algoritam.");











    printf("%s\n", "START test in collide linkedlist mode with DJB2 hash algoritam.");
    
    //init datatype, DSH_DJB2 hash algoritam, DSHM_LINKEDLIST for collide mode
    hs = dshs_create(table_size, DSH_DJB2, DSHM_LINKEDLIST);
       
    //set data
    dshs_set(&hs, "test_key_one", "HELLOWORLD1");
    dshs_set(&hs, "test_key_two", "HELLOWORLD2");
    dshs_set(&hs, "test_key_three", "HELLOWORLD3");
    dshs_set(&hs, "test_key_four", "HELLOWORLD4");
    dshs_set(&hs, "test_key_five", "HELLOWORLD5");
    dshs_set(&hs, "test_key_six", "HELLOWORLD6");
    
    //convert to linkedlist and print members, TODO: write dshs_forEach() with compatible helper functions
    printf("\n%s\n", "Print members: ");
    DSLinkedList *collect_ll = dshs_convertToLinkedList(hs);
    dsll_forEach(&collect_ll, ds_printPairs_hfunc);
    printf("%s\n\n", "End Print members. ");
    dsll_terminate(&collect_ll);
    
    //get data with key 'test_key_four'
    printf(" dshs_get(&hs, test_key_four): %s\n", dshs_get(&hs, "test_key_four"));    
    
    //check collides/members size
    printf(" dshs_countCollides: %d\n", dshs_countCollides(hs));
    printf(" dshs_countMembers: %d\n", dshs_countMembers(hs) );
    
    //overwrite data
    dshs_set(&hs, "test_key_four", "dshs_set_new_data_here");    
    printf(" overwrite dshs_get(&hs, test_key_four): %s\n", dshs_get(&hs, "test_key_four"));  
        
    
    //garbage collect
    dshs_destroy(&hs);
    
    printf("\n%s\n", "END test in collide linkedlist mode with DJB2 hash algoritam.");








}
