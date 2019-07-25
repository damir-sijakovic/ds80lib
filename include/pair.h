#ifndef	DS_PAIR_H
#define	DS_PAIR_H

#define DS_PAIR_KEY_MAX_LENGTH 256 
#define DS_PAIR_KEY_MIN_LENGTH 2
#define DS_PAIR_STRING_DATA_LIMIT 1024


typedef enum {
    DSPE_TYPE_START = 10064, 
    DSPE_TYPE_STRING, 
    DSPE_TYPE_NUMBER, //double
    DSPE_TYPE_BOOLEAN, 
    DSPE_TYPE_NULL, 
    DSPE_TYPE_UNKNOWN, 
    DSPE_TYPE_END, 
} DSPairTypeEnum;
    
typedef struct DSPair{
    char *key;
    char data[1];
} DSPair;
    
// DSPair adt must be deallocated with free()    
DSPair *dspr_newNumber(char *key, double n);
DSPair *dspr_newString(char *key, char *str);
DSPair *dspr_newBoolean(char *key, boolean b);
DSPair *dspr_newNull(char *key);
double dspr_getNumber(DSPair *handle);
char *dspr_getString(DSPair *handle);
boolean dspr_getBoolean(DSPair *handle); 
DSPairTypeEnum dspr_typeOf(DSPair *handle);    
char *dspr_getKey(DSPair *handle);
size_t dspr_getStringSize(DSPair *handle);
char *dspr_toJson(DSPair *handle);
char *dspr_toJsonStripped(DSPair *handle);  


#endif
