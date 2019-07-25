# DS80LIB c library 
#### Version 0.60 

C data structures. Written as a test of code reusability in C language.
Released in the BSD licence. Most of the code is written by me (Damir Šijaković) 
and some parts are from public domain code found on internet.

## Structures

 * DSVector - dynamically resizable array
 * DSLinkedlist - plain one direction linked list
 * DSHashtable - hash table using DSVector/DSLinkedList
 * DSPair - key/pair datatype with JSON export (will be used with DSVector as part of DSJson)
 * DSChunk - basic keyname chunk with size;
 
Future plans:

 * DSSend - send data to file/port/sql
 * DSJson - parse json strings
 * DSString - string datatype with JS like functions
 
## Current status
 
'ds80lib' is still in early development and it doesn't build as whole yet. 
Even though you could make object (.o) files and link all together in one lib.
Best way to play around with these is to wipe everything from test.c/main() and use compile.sh inside module directory. 
Development is done in module directories. So to compile run test.sh in module directory.  
Lib/code is tested under ArchLinux/openrc 5.1 kernel and Valgrind 3.14.
Documentation is in [ds80lib_docs.html](http://htmlpreview.github.io/?https://github.com/damir-sijakovic/ds80lib/blob/master/ds80lib_docs.html) file.


## Interface 

### DSVector

        typedef struct DSVector{     
            size_t length;
            DSVectorMode mode;
            int step;
            void * data[1];    
        } DSVector;  


        DSVector *dsv_create(size_t size, DSVectorMode mode, int step);
        DSVector *dsv_clone(DSVector *handle); //clones adt object
        void dsv_destroy(DSVector *handle);
        int dsv_resize(DSVector **handle, size_t length);
        boolean dsv_set(DSVector **handle, unsigned index, void * data); 
        void *dsv_get(DSVector *handle, unsigned index);
        int dsv_shrinkToFit(DSVector **handle);
        boolean dsv_forEach(DSVector **handle, boolean (*fn_ptr)(void **));
        int dsv_forEachComplex(DSVector **handle, int (*fn_ptr)(void**, void**), void **data); 
        void *dsv_forEachData(DSVector **handle, void *(*fn_ptr)(void**, void**), void **data);  
        void **dsv_getContainer(DSVector **handle, unsigned index);

        int dsv_push(DSVector **handle, void *data); 
        void *dsv_pop(DSVector **handle);
        int dsv_unshift(DSVector **handle, void *data);
        void *dsv_shift(DSVector **handle);
        void dsv_nullify(DSVector **v); 
        size_t dsv_getByteSize(DSVector *v); 
        boolean dsv_reverse(DSVector **v);
        boolean dsv_compare(DSVector *a, DSVector *b);
        int dsv_areMembers(DSVector *v, void *data, unsigned start_index); 
        void *dsv_removeMember(DSVector **handle, unsigned idx);
        int dsv_insertMember(DSVector **handle, unsigned idx, void *data);   
        void dsv_swapMembers(DSVector **handle, unsigned idx_a, unsigned idx_b);
        DSVector *dsv_merge(DSVector *a, DSVector *b);
        void dsv_firstToLast(DSVector **handle);
        void dsv_lastToFirst(DSVector **handle);
        boolean dsv_isNull(DSVector *handle, unsigned idx);
        int dsv_countUsed(DSVector *handle);
        int dsv_countFree(DSVector *handle);

### DSLinkedList

        typedef struct DSNode {    
            void *data;
            struct DSNode *next;
        } DSNode;

        typedef struct DSLinkedList {    
            unsigned length;
            struct DSNode *head;
            struct DSNode *tail;
        } DSLinkedList;


        DSLinkedList *dsll_initilize();
        DSNode *dsll_createNode(void *data);
        int dsll_terminate(DSLinkedList **l);
        size_t dsll_push(DSLinkedList **l, void *data);
        void *dsll_pop(DSLinkedList **l); //rem last pass rem data
        size_t dsll_unshift(DSLinkedList **l, void *val); //add first return length
        void *dsll_shift(DSLinkedList **l); //rem first and return value
        void dsll_firstToLast(DSLinkedList **l);
        void dsll_lastToFirst(DSLinkedList **l);
        boolean dsll_forEach(DSLinkedList **l, boolean (*pf)(void**)); 
        int dsll_forEachComplex(DSLinkedList **l, int (*pf)(void**, void**), void **data);
        void *dsll_forEachData(DSLinkedList **l, void* (*pf)(void**, void**), void **data); 
        void *dsll_get(DSLinkedList *l, unsigned index);
        void *dsll_set(DSLinkedList *l, unsigned index, void *data);
        boolean dsll_dataExists(DSLinkedList *l, void *data);  
        DSLinkedList *dsll_merge(DSLinkedList *a, DSLinkedList *b);
        boolean dsll_find(DSLinkedList **l, DSNode **n, unsigned idx);
        int dsll_findPrev(DSLinkedList **l, DSNode **prev, unsigned idx);
        void *dsll_findData(DSLinkedList **l, void *data);   
        DSNode *dsll_findDataGetNode(DSLinkedList **l, void *data);
        int dsll_findDataIndex(DSLinkedList **l, void *data);  
        int dsll_findPrevData(DSLinkedList **l, DSNode **prev, void *data); 
        boolean dsll_swap(DSLinkedList *l, unsigned idx_a, unsigned idx_b);

        //linkedlist <=> vector
        DSLinkedList *dsll_vectorToLinkedList(DSVector *v);
        DSVector *dsll_linkedListToVector(DSLinkedList *l);
        DSLinkedList *dsll_reverse(DSLinkedList *l);


### DSPair

        typedef struct DSPair{
            char *key;
            char data[1];
        } DSPair;
            
        // DSPair adt must be deallocated with free()    
        DSPair *dspr_newNumber(char *key, double n);
        int dspr_typeOf(DSPair *handle);    
        DSPair *dspr_setNumber(DSPair **handle, double n);
        double dspr_getNumber(DSPair *handle);    
        DSPair *dspr_newString(char *key, char *str);
        char *dspr_getString(DSPair *handle);
        size_t dspr_getStringSize(DSPair *handle);
        DSPair *dspr_newBoolean(char *key, boolean b);
        boolean dspr_getBoolean(DSPair *handle);   
        DSPair *dspr_newNull(char *key);
        char *dspr_toJson(DSPair *handle);
        char *dspr_toJsonStripped(DSPair *handle);  
        char *dspr_getKey(DSPair *handle);
        
        
        
### DSHashtable

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


### Copyright and license

Damir Šijaković (c) 2019, BSD Licence 
