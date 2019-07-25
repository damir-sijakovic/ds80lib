#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "../include/dslib.h"
#include "../include/vector.h"

void dsv_debug_print(DSVector *handle, char *str){
    
    printf("%s\n", "========= DEBUG PRINT =========");
    printf("%s\n", str );
    int i = 0;
    for (; i<handle->length; i++){
        if (handle->data[i] == NULL){
            printf("%s\n", "-null-");
            continue;
        }
        printf("[%d] %s\n", i, handle->data[i]);
    }
    printf("Vector length is: %d\n", handle->length);
    printf("%s\n", "========= DEBUG END =========");
}


boolean pf_test(void **a){
   // printf("%s\n", *a);
    *a = "Overwrite with dsv_forEach.";  
    return TRUE;  
}

int main(){
    
    DSVector *v1 = dsv_create(0, DS_VECTOR_MODE_STEP, 1);
    
    dsv_push(&v1, "00 -- ");
    dsv_push(&v1, "01 -- ");
    dsv_push(&v1, "02 -- ");
    dsv_push(&v1, "03 -- ");
    
    dsv_set(&v1, 6, NULL);
    
    dsv_debug_print(v1, "=== TEST1 ===" );    
    dsv_destroy(v1);
    
    
    /*
    //void dsv_firstToLast(DSVector **handle){
    //void dsv_lastToFirst(DSVector **handle){
    
    DSVector *v1 = dsv_create(0, DS_VECTOR_MODE_STEP, 1);
    
    dsv_push(&v1, "00 -- ");
    dsv_push(&v1, "01 -- ");
    dsv_push(&v1, "02 -- ");
    dsv_push(&v1, "03 -- ");
    
    dsv_set(&v1, 6, NULL);
    
    if (dsv_isNull(v1, 5)){
        printf("%s\n", "sv_isNull(v1, 5) is NULL.");
    }
    //dsv_lastToFirst(&v1);
    dsv_firstToLast(&v1);
    
    dsv_debug_print(v1, "=== TEST1 ===" );    
    dsv_destroy(v1);
    */
    
    
    /*
    //dsv_merge

    DSVector *v1 = dsv_create(0, DS_VECTOR_MODE_STEP, 1);
    dsv_push(&v1, "00 -- ");
    dsv_push(&v1, "01 -- ");
    dsv_push(&v1, "02 -- ");
    dsv_push(&v1, "03 -- ");
  
    DSVector *v2 = dsv_create(0, DS_VECTOR_MODE_STEP, 1);
    dsv_push(&v2, "11 -- ");
    dsv_push(&v2, "12 -- ");
    dsv_push(&v2, "13 -- ");
    dsv_push(&v2, "14 -- ");
  
    DSVector *v3 = dsv_merge(v1, v2);
    
    dsv_debug_print(v3, "=== TEST1 ===" );    
    dsv_destroy(v1);
    */
    
    
    /*

    // dsv_swapMembers, dsv_insertMember 
    
    DSVector *vtr = dsv_create(0, DS_VECTOR_MODE_STEP, 1);
    dsv_push(&vtr, "00 -- ");
    dsv_push(&vtr, "01 -- ");
    dsv_push(&vtr, "02 -- ");
    dsv_push(&vtr, "03 -- ");
    dsv_push(&vtr, "04 -- ");
    dsv_push(&vtr, "05 -- ");
    dsv_push(&vtr, "06 -- ");
    
    dsv_insertMember(&vtr, 2, "hello world");
    
    dsv_swapMembers(&vtr, 2, 5);
    
    
    dsv_debug_print(vtr, "=== TEST1 ===" );    
    dsv_destroy(vtr);
    */
    
    /*
    
    //dsv_removeMember()
    
    DSVector *vtr = dsv_create(0, DS_VECTOR_MODE_STEP, 1);
    
    dsv_push(&vtr, "00 -- ");
    dsv_push(&vtr, "01 -- ");
    dsv_push(&vtr, "02 -- ");
    dsv_push(&vtr, "03 -- ");
    dsv_push(&vtr, "04 -- ");
    dsv_push(&vtr, "05 -- ");
    dsv_push(&vtr, "06 -- ");
    dsv_push(&vtr, "07 -- ");
    dsv_push(&vtr, "08 -- ");
    dsv_push(&vtr, "09 -- ");
    dsv_push(&vtr, "10 -- ");
    dsv_push(&vtr, "11 -- ");
    dsv_push(&vtr, "12 -- ");
    dsv_push(&vtr, "13 -- ");
    dsv_push(&vtr, "14 -- ");
    dsv_push(&vtr, "15 -- ");
    dsv_push(&vtr, "16 -- ");
    dsv_push(&vtr, "17 -- ");
    dsv_push(&vtr, "18 -- ");
    dsv_push(&vtr, "19 -- ");
    dsv_push(&vtr, "20 -- ");
    dsv_push(&vtr, "21 -- ");
    
    dsv_removeMember(&vtr, 10); 
    
    dsv_debug_print(vtr, "=== TEST1 ===" );    
    dsv_destroy(vtr);
    
    */
    
    
    /*
    DSVector *vtr = dsv_create(0, DS_VECTOR_MODE_STEP, 1);
    
    char *al = "archlinux";
    char *al3 = "efefefe";
    
    dsv_push(&vtr, "00 -- ");
    dsv_push(&vtr, "01 -- ");
    dsv_push(&vtr, al);
    dsv_push(&vtr, "02 -- ");
    dsv_push(&vtr, "03 -- ");
    
    printf("found at: %d\n", dsv_areMembers(vtr, al, 2) );
    
    dsv_debug_print(vtr, "=== TEST1 ===" );    
    dsv_destroy(vtr);
    */
    
    // TEST1: create vector and add items     
    //DSVector *vtr = dsv_create(0, DS_VECTOR_MODE_STEP, 1);
    
    //dsv_push(&vtr, "00 -- ");
    //dsv_push(&vtr, "01 -- ");
    //dsv_push(&vtr, "02 -- ");
    //dsv_push(&vtr, "03 -- ");
    
    //dsv_reverse(&vtr);
    
    /*
    dsv_unshift(&vtr, "new data 1");
    dsv_unshift(&vtr, "new data 2");
    dsv_unshift(&vtr, "new data 3");
        
    void *somdat = dsv_shift(&vtr); 
    printf("%s\n", some data  );

    */
    
/*
    void *out = dsv_pop(&vtr);
    printf(">>> %s\n",out);
*/
    /*
    dsv_set(&vtr, 0, "0:insert"); 
    dsv_set(&vtr, 1, "1:insert");  
    dsv_set(&vtr, 2, "2:insert");  
    dsv_set(&vtr, 3, "3:insert");  
    dsv_set(&vtr, 4, "4:insert");  
    dsv_set(&vtr, 5, "5:insert");  
    dsv_set(&vtr, 9, "9:insert");
    */
        
    //printf("dsv_get: %s\n", dsv_get(vtr, 3 ));    
        
    //dsv_debug_print(vtr, "=== TEST1 ===" );
    //dsv_destroy(vtr);
    
        
    /*    
    // TEST2: resize vector   
    DSVector *vtr = dsv_create(2, DS_VECTOR_MODE_STEP, 2);
    dsv_set(&vtr, 0, "0:insert"); 
    dsv_set(&vtr, 1, "1:insert");  
    dsv_set(&vtr, 2, "2:insert");  
    dsv_set(&vtr, 3, "3:insert");  
    dsv_set(&vtr, 4, "4:insert");  
    dsv_set(&vtr, 5, "5:insert");  
    dsv_set(&vtr, 9, "9:insert");
    
    dsv_resize(&vtr, 3);
    
    dsv_debug_print(vtr, "=== TEST2: resize to 3 items ===" );
    
    dsv_resize(&vtr, 20);
    dsv_debug_print(vtr, "=== TEST2: resize to 20 items ===" );
    
    dsv_shrinkToFit(&vtr); 
    dsv_debug_print(vtr, "=== TEST2: dsv_shrinkToFit() ===" );
    
    dsv_destroy(vtr);
    */
    
    
    /*
    // TEST3: double resize mode, dsv_forEach() and dsv_getContainer()
    DSVector *vtr = dsv_create(1, DS_VECTOR_MODE_DOUBLE, 2);
    dsv_set(&vtr, 0, "0:insert"); 
    dsv_set(&vtr, 1, "1:insert");  
    dsv_set(&vtr, 2, "2:insert");  
    dsv_set(&vtr, 3, "3:insert");  
    dsv_set(&vtr, 4, "4:insert");  
    dsv_set(&vtr, 5, "5:insert");  
    dsv_set(&vtr, 9, "9:insert");
    
    void **data_address = dsv_getContainer(&vtr, 4);
    *data_address = "Changed stuff at index 4.";
    
    dsv_debug_print(vtr, "=== TEST3: dsv_getContainer() ===");
    
    dsv_forEach(&vtr, pf_test); 
    
    dsv_debug_print(vtr, "=== TEST3: dsv_forEach() ===");
    
    dsv_destroy(vtr);
    */

}
