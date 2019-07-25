#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "../include/dslib.h"
#include "../include/vector.h"
#include "../include/linkedlist.h"

boolean lls_pf_test(void **a){
    //printf("lls_pf_test: %s\n", *a);
   *a = "ddd";    
}

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


void dsll_debugPrint(DSLinkedList **l){
    printf("%s\n", "=================================");
    DSNode *t = (*l)->head;    
    unsigned i = 0;
    
    for (; i < (*l)->length; i++){        
        printf("%s\n", t->data); 
        t = t->next;
    }   
    printf("Vector length is: %d\n", (*l)->length); 
}

void ds_is_null(void *a){
    if (a == NULL){
        printf("%s\n", "is null!");
    }
}

int main(){
    
    // push, pop, shift, unshift
    DSLinkedList *l1 = dsll_initilize();
    dsll_push(&l1, "00 string ");
    dsll_push(&l1, "01 string ");
    dsll_push(&l1, "02 string ");
    printf("dsll_pop: %s\n", dsll_pop(&l1) ); 
    dsll_unshift(&l1, "03 string ");
    dsll_unshift(&l1, "04 string ");
    dsll_unshift(&l1, "05 string ");

    printf("dsll_shift: %s\n", dsll_shift(&l1) ); 

    dsll_debugPrint(&l1);
    dsll_terminate(&l1);
   
}
