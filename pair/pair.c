#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "../include/dslib.h"
#include "../include/pair.h"



void dspr_error(char *msg){
    fprintf(stderr, "dslib error: %s \n", msg);
    exit(EXIT_FAILURE);
}


DSPairTypeEnum dspr_typeOf(DSPair *handle){
    assert(handle);
    assert(handle->key); 
    
    if (handle->data[0] != '$'){
        dspr_error("Not a DSPair data.");
    }
    
    char type = handle->data[1]; 
    if (type == 'G') return DSPE_TYPE_NUMBER;
    if (type == 'S') return DSPE_TYPE_STRING;
    if (type == 'B') return DSPE_TYPE_BOOLEAN;
    if (type == 'N') return DSPE_TYPE_NULL;
    
    return DSPE_TYPE_UNKNOWN;    
}

DSPair *dspr_newNumber(char *key, double n){
    size_t keysize = strlen(key);
    assert(keysize < DS_PAIR_KEY_MAX_LENGTH);
    assert(keysize > DS_PAIR_KEY_MIN_LENGTH);
    
    size_t malloc_size = sizeof (DSPair) + keysize + sizeof(double) + 6;  //5+1 
    DSPair *pr = malloc(malloc_size);
    memset(pr, 0, malloc_size);  
    char *type_code = "$G$\0"; 

    memcpy(&pr->data[0], type_code, 4);      
    memcpy(&pr->data[4], key, keysize);  
    
    pr->key = &pr->data[4];
   
    pr->data[keysize+4] = '\0';
    memcpy(&pr->data[4], key, keysize);  
    
    memcpy(&pr->data[4+keysize+1], &n, sizeof(double)); 
   
    return pr;    
}

double dspr_getNumber(DSPair *handle){    
    assert(handle); 
    
    if (dspr_typeOf(handle) != DSPE_TYPE_NUMBER){
        dspr_error("Not a DSPair number datatype.");
    }

    int number_start = 5 + strlen(handle->key); 
    
    double *d = (double*) &handle->data[number_start];
    return *d; 
}

DSPair *dspr_newBoolean(char *key, boolean b){
    size_t keysize = strlen(key);
    assert(keysize < DS_PAIR_KEY_MAX_LENGTH);
    assert(keysize > DS_PAIR_KEY_MIN_LENGTH);
    
    size_t malloc_size = sizeof (DSPair) + keysize + sizeof(unsigned char) + 6;  //5+1 
    DSPair *pr = malloc(malloc_size);
    memset(pr, 0, malloc_size);  
    memset(pr->data, '*', malloc_size - sizeof (DSPair) -1);  
    
    
    char *type_code = "$B$\0"; 
    memcpy(&pr->data[0], type_code, 4);      
    memcpy(&pr->data[4], key, keysize);  
        
    pr->data[keysize+4] = '\0';
    memcpy(&pr->data[4], key, keysize); 
    pr->key = &pr->data[4]; 
    
    if (b){
        memcpy(&pr->data[4+keysize+1], "1", 1); 
    }
    else {
        memcpy(&pr->data[4+keysize+1], "0", 1); 
    }
       
    return pr;    
}

DSPair *dspr_newNull(char *key){
    size_t keysize = strlen(key);
    assert(keysize < DS_PAIR_KEY_MAX_LENGTH);
    assert(keysize > DS_PAIR_KEY_MIN_LENGTH);
    
    size_t malloc_size = sizeof (DSPair) + keysize + 6; 
    DSPair *pr = malloc(malloc_size);
    memset(pr, 0, malloc_size);  
    memset(pr->data, '*', malloc_size - sizeof (DSPair) -1);  
    
    
    char *type_code = "$N$\0"; 
    memcpy(&pr->data[0], type_code, 4);      
    memcpy(&pr->data[4], key, keysize);  
        
    pr->data[keysize+4] = '\0';
    memcpy(&pr->data[4], key, keysize); 
    pr->key = &pr->data[4]; 
    
    return pr;    
}

boolean dspr_getBoolean(DSPair *handle){    
    assert(handle); 
    
    if (dspr_typeOf(handle) != DSPE_TYPE_BOOLEAN){
        dspr_error("Not a DSPair boolean datatype.");
    }
    
    int bool_start = 5 + strlen(handle->key); 
    char *ret = (boolean*) &handle->data[bool_start];
    
    if (ret[0] == '1'){
        return TRUE;
    }
    else if (ret[0] == '0'){
        return FALSE;
    }
       
    // else
    dspr_error("Not a DSPair boolean datatype.");  
}


//"$S20$\0key\0String data is here."  
DSPair *dspr_newString(char *key, char *str){
    size_t keysize = strlen(key);
    assert(keysize < DS_PAIR_KEY_MAX_LENGTH);
    assert(keysize > DS_PAIR_KEY_MIN_LENGTH);
    
    size_t string_size = strlen(str);
    assert(string_size < DS_PAIR_STRING_DATA_LIMIT);
    
    char sizeString[32];
    sprintf(sizeString, "%d", string_size); 
    size_t sizeString_size = strlen(sizeString);
    
    size_t malloc_size = sizeof (DSPair) + keysize + string_size + sizeString_size + 6;  //5+1 

    DSPair *t = malloc(malloc_size);
    memset(t, 0, malloc_size);  

    int idx = 0;   
    memcpy(&t->data[0], "$S", 2);  
    idx += 2;    
    memcpy(&t->data[idx], sizeString, sizeString_size); 
    idx += sizeString_size;
    memcpy(&t->data[idx], "$\0", 2); 

    idx += 2;
    
    t->key = &t->data[idx];
    
    memcpy(&t->data[idx], key, keysize); 
    idx += keysize; 
    memcpy(&t->data[idx], "\0", 1); 
    idx += 1;     
    memcpy(&t->data[idx], str, string_size); 
    idx += string_size; 

 
    return t;
}

size_t dspr_getStringSize(DSPair *handle){
    assert(handle); 
    
    if (dspr_typeOf(handle) != DSPE_TYPE_STRING){
        dspr_error("Not a DSPair string datatype.");
    }
   
    int i = 2;
    for (; i<DS_PAIR_KEY_MAX_LENGTH; i++){
        if (handle->data[i] == '$') break;
    }
    
    size_t msize = (i-2) + 1;
    char *size_str = malloc(msize);
    memset(size_str, 0, msize);
    memcpy(size_str, &handle->data[2], i-2); 
    
    
    int num = atoi(size_str); //set limit
    free(size_str);
    
    return num;      
}

char *dspr_getString(DSPair *handle){
    assert(handle); 
    
    if (dspr_typeOf(handle) != DSPE_TYPE_STRING){
        dspr_error("Not a DSPair string datatype.");
    }
    
    int string_start = 1;
    int found_first = 0;
    for (; string_start<32; string_start++){ //32 number to string
        if (found_first && handle->data[string_start] == '\0'){
            string_start++;
            break;
        }     
        
        if (handle->data[string_start] == '$'){
            found_first = 1;
            string_start += 2;
        }
    }

    return &handle->data[string_start];
    
}

char *dspr_toJson(DSPair *handle){
    assert(handle); 
    
    //{"key":"string value"} 7+1
    //{"key":32.31} 5+1
    //{"key":true} 5+1
    //{"key":null} 5+1
    char *retstr = NULL;
    size_t retstr_size = 0;
    unsigned mempen = 0;  
    
        
    if (dspr_typeOf(handle) == DSPE_TYPE_STRING){     
        size_t key_size = strlen(handle->key);     
        size_t value_size = dspr_getStringSize(handle); //what if string is ""? DO: if strlen == 0 {"k":""}     
        retstr_size = key_size + value_size + (8+1);
        retstr = malloc(retstr_size);
        memset(retstr, 0, retstr_size);
        
        mempen = 0;        
        retstr[mempen] = '{';
        mempen += 1;
        retstr[mempen] = '"';
        mempen += 1;
        
        memcpy(&retstr[mempen], handle->key, key_size);
        mempen += key_size;        
        memcpy(&retstr[mempen], "\": \"", 4);
        mempen += 4; 
        
        memcpy(&retstr[mempen], dspr_getString(handle), value_size);
        mempen += value_size; 
        memcpy(&retstr[mempen], "\"}", 2);
        
        return retstr;
        
    }    
    else if (dspr_typeOf(handle) == DSPE_TYPE_NUMBER){   
        size_t key_size = strlen(handle->key);
        
        char strNumber[32];
        sprintf(strNumber, "%g", dspr_getNumber(handle)); 
        size_t strNumber_size = strlen(strNumber);
                
        retstr_size = key_size + sizeof(double) + strNumber_size + (6+1);
        retstr = malloc(retstr_size);
        memset(retstr, 0, retstr_size);
        
        mempen = 0;   
        retstr[mempen] = '{';
        mempen += 1;
        retstr[mempen] = '"';
        mempen += 1;
        memcpy(&retstr[mempen], handle->key, key_size);
        mempen += key_size;  
        memcpy(&retstr[mempen], "\": ", 3);
        mempen += 3; 
        memcpy(&retstr[mempen], strNumber, strNumber_size);
        mempen += strNumber_size; 
        memcpy(&retstr[mempen], "}", 1);
        
        return retstr;        
    }
    else if (dspr_typeOf(handle) == DSPE_TYPE_BOOLEAN){   
        size_t key_size = strlen(handle->key);
        
        boolean is_true = dspr_getBoolean(handle);        
        size_t boolean_str_size = is_true ? 4 : 5;  
                
        retstr_size = key_size + sizeof(double) + boolean_str_size + (6+1);
        retstr = malloc(retstr_size);
        memset(retstr, 0, retstr_size);
        
        mempen = 0;   
        retstr[mempen] = '{';
        mempen += 1;
        retstr[mempen] = '"';
        mempen += 1;
        memcpy(&retstr[mempen], handle->key, key_size);
        mempen += key_size;  
        memcpy(&retstr[mempen], "\": ", 3);
        mempen += 3; 
        if (is_true){
            memcpy(&retstr[mempen], "true", 4);
            mempen += 4; 
        }
        else {
            memcpy(&retstr[mempen], "false", 5);
            mempen += 5; 
        }
        
        memcpy(&retstr[mempen], "}", 1);
        
        return retstr;        
    }
    else if (dspr_typeOf(handle) == DSPE_TYPE_NULL){   
        size_t key_size = strlen(handle->key);        
                
        retstr_size = key_size + sizeof(double) + 4 + (6+1);
        retstr = malloc(retstr_size);
        memset(retstr, 0, retstr_size);
        
        mempen = 0;   
        retstr[mempen] = '{';
        mempen += 1;
        retstr[mempen] = '"';
        mempen += 1;
        memcpy(&retstr[mempen], handle->key, key_size);
        mempen += key_size;  
        memcpy(&retstr[mempen], "\": ", 3);
        mempen += 3; 
        memcpy(&retstr[mempen], "null", 4);
        mempen += 4; 
        memcpy(&retstr[mempen], "}", 1);
        
        return retstr;        
    }
    else {
        dspr_error("Not a DSPair datatype.");
    }   
        
}

char *dspr_toJsonStripped(DSPair *handle){
    assert(handle); 
    
    char *retstr = NULL;
    size_t retstr_size = 0;
    unsigned mempen = 0;  
    
        
    if (dspr_typeOf(handle) == DSPE_TYPE_STRING){     
        size_t key_size = strlen(handle->key);     
        size_t value_size = dspr_getStringSize(handle); //what if string is ""? => {"k":""}     
        retstr_size = key_size + value_size + (6+1);
        retstr = malloc(retstr_size);
        memset(retstr, 0, retstr_size);
        
        mempen = 0;        
        retstr[mempen] = '"';
        mempen += 1;
        
        memcpy(&retstr[mempen], handle->key, key_size);
        mempen += key_size;        
        memcpy(&retstr[mempen], "\": \"", 4);
        mempen += 4; 
        
        memcpy(&retstr[mempen], dspr_getString(handle), value_size);
        mempen += value_size; 
        memcpy(&retstr[mempen], "\"", 1);
        
        return retstr;
        
    }    
    else if (dspr_typeOf(handle) == DSPE_TYPE_NUMBER){   
        size_t key_size = strlen(handle->key);
        
        char strNumber[32];
        sprintf(strNumber, "%g", dspr_getNumber(handle)); 
        size_t strNumber_size = strlen(strNumber);
                
        retstr_size = key_size + sizeof(double) + strNumber_size + (4+1);
        retstr = malloc(retstr_size);
        memset(retstr, 0, retstr_size);
        
        mempen = 0;   
        retstr[mempen] = '"';
        mempen += 1;
        memcpy(&retstr[mempen], handle->key, key_size);
        mempen += key_size;  
        memcpy(&retstr[mempen], "\": ", 3);
        mempen += 3; 
        memcpy(&retstr[mempen], strNumber, strNumber_size);
        
        return retstr;        
    }
    else if (dspr_typeOf(handle) == DSPE_TYPE_BOOLEAN){   
        size_t key_size = strlen(handle->key);
        
        boolean is_true = dspr_getBoolean(handle);        
        size_t boolean_str_size = is_true ? 4 : 5;  
                
        retstr_size = key_size + sizeof(double) + boolean_str_size + (4+1);
        retstr = malloc(retstr_size);
        memset(retstr, 0, retstr_size);
        
        mempen = 0;   
        retstr[mempen] = '"';
        mempen += 1;
        memcpy(&retstr[mempen], handle->key, key_size);
        mempen += key_size;  
        memcpy(&retstr[mempen], "\": ", 3);
        mempen += 3; 
        if (is_true){
            memcpy(&retstr[mempen], "true", 4);
        }
        else {
            memcpy(&retstr[mempen], "false", 5);
        }        
        
        return retstr;        
    }
    else if (dspr_typeOf(handle) == DSPE_TYPE_NULL){   
        size_t key_size = strlen(handle->key);        
                
        retstr_size = key_size + sizeof(double) + 4 + (4+1);
        retstr = malloc(retstr_size);
        memset(retstr, 0, retstr_size);
        
        mempen = 0;   
        retstr[mempen] = '"';
        mempen += 1;
        memcpy(&retstr[mempen], handle->key, key_size);
        mempen += key_size;  
        memcpy(&retstr[mempen], "\": ", 3);
        mempen += 3; 
        memcpy(&retstr[mempen], "null", 4);
        
        return retstr;        
    }
    else {
        dspr_error("Not a DSPair datatype.");
    }   
}

char *dspr_getKey(DSPair *handle){
    assert(handle); assert(handle->key);
    
    return handle->key;
}

/*
 // PREPARE FOR WRITE HEX 
 
void ds_byte2hex(unsigned char byte, char *hexstr){  //passin hexstr[2] 
    sprintf(&hexstr[0], "%02X", byte); 
}

unsigned char ds_hex2byte(char *hexstr){    
    return strtoul("6E", 0, 16);    
}

int ds_isHexByte(char *hexstr){
    if (strlen != 2){
        return -1
    }
    if (s[strspn(s, "0123456789abcdefABCDEF")] == 0){
        return 1;
    }
    return -1;    
}
  
 */

