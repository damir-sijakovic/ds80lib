#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "../include/dslib.h"
#include "../include/pair.h"


int main(){
    
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
    
}


