/* damir: more code reusability test in c then a proper hashtable abstruct */

#ifndef	DS_HASHTABLE_H
#define	DS_HASHTABLE_H
    
#define DS_HASHTABLE_TABLE_LOWER_LIMIT 2 
//#define DS_HASHTABLE_TABLE_LOWER_LIMIT 31 //default: 31
#define DS_HASHTABLE_TABLE_UPPER_LIMIT DS_VECTOR_ITEM_LIMIT // change DS_VECTOR_ITEM_LIMIT in vector.h
#define DS_HASHTABLE_KEYSTR_LIMIT 1024 
#define DSHS_FNV_PRIME_32 16777619
#define DSHS_FNV_OFFSET_32 2166136261U

//debug
//#define DS_HS_SIMULATE_COLLIDE 1 // put everything to bucket in last index 


typedef enum {
    DSH_START = 0, 
    DSH_RAMAKRISHNA, 
    DSH_DJB2, 
    DSH_SDBM, 
    DSH_FNV32, 
    DSH_END, 
} DSHashTableEnum;

typedef enum {
    DSHM_START = 0, 
    DSHM_LINKEDLIST, 
    DSHM_VECTOR, 
    DSHM_END, 
} DSHashTableModeEnum;


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



DSHashTable *dshs_create(unsigned size, DSHashTableEnum hash, DSHashTableModeEnum mode);
int dshs_destroy(DSHashTable **handle);
int dshs_set(DSHashTable **handle, char *key, void *data);
void *dshs_get(DSHashTable **handle, char *key);
int dshs_countCollides(DSHashTable *handle);
int dshs_countMembers(DSHashTable *handle);
int dshs_toPrime(int num);
DSVector *dshs_convertToVector(DSHashTable *handle);
DSLinkedList *dshs_convertToLinkedList(DSHashTable *handle);
    
#endif
