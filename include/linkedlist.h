#ifndef	DS_LINKEDLIST_H
#define	DS_LINKEDLIST_H

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
boolean dsll_forEach(DSLinkedList **l, boolean (*pf)(void**)); // pf returns boolean to dsll_forEach. dsll_forEach returns FALSE by default 
int dsll_forEachComplex(DSLinkedList **l, int (*pf)(void**, void**), void **data); //pass additional 'data' arg to pf(), returns int useful as return codes, if pf returns nothing dsll_forEachComplex returns 0
void *dsll_forEachData(DSLinkedList **l, void* (*pf)(void**, void**), void **data); //pass additional 'data' arg to pf(), returns void*, if pf returns nothing dsll_forEachComplex returns NULL
void *dsll_get(DSLinkedList *l, unsigned index);
void *dsll_set(DSLinkedList *l, unsigned index, void *data);
boolean dsll_dataExists(DSLinkedList *l, void *data);  
DSLinkedList *dsll_merge(DSLinkedList *a, DSLinkedList *b);
boolean dsll_find(DSLinkedList **l, DSNode **n, unsigned idx);
int dsll_findPrev(DSLinkedList **l, DSNode **prev, unsigned idx); //Return code - 0: empty list, -1: no prev item, 1: found data
DSNode *dsll_findDataGetNode(DSLinkedList **l, void *data);
int dsll_findDataIndex(DSLinkedList **l, void *data);  
int dsll_findPrevData(DSLinkedList **l, DSNode **prev, void *data); //Return code - 0: empty list, -1: no prev item, 1: found data
boolean dsll_swap(DSLinkedList *l, unsigned idx_a, unsigned idx_b);

//vector
DSLinkedList *dsll_vectorToLinkedList(DSVector *v);
DSVector *dsll_linkedListToVector(DSLinkedList *l);
DSLinkedList *dsll_reverse(DSLinkedList *l);




#endif
