#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "../include/dslib.h"
#include "../include/pair.h"

void dspr_debugPrint(DSPair *handle){    
    assert(handle);

    printf("DSPair Debug: %s", "");
    size_t iteration_length = 1; 
    if (handle->data[iteration_length] == 'S'){ // type is string
        int count_null = 0, i = 0;        
        for (;count_null<2 ; i++){
            if (handle->data[i] == '\0'){
                printf("%s", "[0]");
                ++count_null;
                continue;
            }
            printf("%c", handle->data[i]);
        }  
        
        printf("%s\n",""); 
        return;     
    }
    if (handle->data[iteration_length] == 'G'){ // type is number
        int count_null = 0, i = 0;        
        for (;count_null<2 ; i++){
            if (handle->data[i] == '\0'){
                printf("%s", "[0]");
                ++count_null;
                continue;
            }
            printf("%c", handle->data[i]);
        }  
        double *number = (double*) &handle->data[i];
        printf("%g", *number); 
        printf("%s\n","");  
        return;    
    }
    if (handle->data[iteration_length] == 'B'){ // type is boolean
        int count_null = 0, i = 0;        
        for (;count_null<2 ; i++){
            if (handle->data[i] == '\0'){
                printf("%s", "[0]");
                ++count_null;
                continue;
            }
            printf("%c", handle->data[i]);
        }          
        printf("%c", handle->data[i]);
        printf("%s\n","");          
        return;    
    }
    if (handle->data[iteration_length] == 'N'){ // type is null
        int count_null = 0, i = 0;        
        for (;count_null<2 ; i++){
            if (handle->data[i] == '\0'){
                printf("%s", "[0]");
                ++count_null;
                continue;
            }
            printf("%c", handle->data[i]);
        }          
        printf("%c", handle->data[i]);
        printf("%s\n","");          
        return;    
    }   
}


int main(){
    
    DSPair *pair = dspr_newNumber("im_long_string_im_long_string_im_long_string_im_long_string_", 33.45);
    double unpack_number = dspr_getNumber(pair);
    printf("%g\n", unpack_number);
    dspr_debugPrint(pair);
    free(pair);
    
    
    /*
    // dspr_debugPrint
    DSPair *pair = dspr_newString("i_am_string", "Some text to store.");
    dspr_debugPrint(pair);
    free(pair);    
    pair = dspr_newNumber("number", 33.45);
    dspr_debugPrint(pair);
    free(pair);    
    pair = dspr_newBoolean("boolean key", TRUE); 
    dspr_debugPrint(pair);
    free(pair); 
    pair = dspr_newNull("Object");
    dspr_debugPrint(pair);
    free(pair); 
    */
    

    /*
    //create types
    DSPair *pr_string = dspr_newString("i_am_string", "Some text to store.");
    DSPair *pr_number = dspr_newNumber("number", 33.45);
    DSPair *pr_boolean = dspr_newBoolean("boolean key", FALSE); 
    DSPair *pr_null = dspr_newNull("Object");
       
    //get key   
    printf("dspr_getKey(pr_boolean) : %s\n", dspr_getKey(pr_boolean));   
       
    //get type 
    if (dspr_typeOf(pr_string) == DSPE_TYPE_STRING){ 
        printf("%s\n", "Variable 'pr_string' is string type.");
        printf("Size of string in 'pr_string' variable is: %d\n", dspr_getStringSize(pr_string));
    }   
    
    //unpack
    double unpack_number = dspr_getNumber(pr_number);
    printf("unpack_number: %g\n", unpack_number);

    //to json
    char *strpen = dspr_toJson(pr_boolean);
    printf("dspr_toJson: %s\n", strpen);    
    free(strpen);
    strpen = dspr_toJsonStripped(pr_number);
    printf("dspr_toJsonStripped: %s\n",  strpen);
    free(strpen);
    
    free(pr_string);
    free(pr_number);
    free(pr_boolean);
    free(pr_null);
    */
}


