#ifndef	DS_VECTOR_H
#define	DS_VECTOR_H
    
/****************************************************************************\
 CONFIG
\****************************************************************************/

#define DS_VECTOR_ITEM_LIMIT 10000
//#define DS_VECTOR_DEBUG_RESIZE 

/****************************************************************************\
 TYPES
\****************************************************************************/

#ifndef FALSE
 #define FALSE (0)
#endif
#ifndef TRUE
 #define TRUE (!FALSE)
#endif
#ifndef boolean
 #define boolean unsigned char
#endif

#define DSVectorMode long 
#define DS_VECTOR_MODE_DOUBLE 0xDB1E
#define DS_VECTOR_MODE_STEP 0x57E9

typedef struct DSVector{     
//boolean lock_size; //no resize functions
    size_t length;
    DSVectorMode mode;
    int step;
    void * data[1];    
} DSVector;  

/****************************************************************************\
 PROTOS
\****************************************************************************/

DSVector *dsv_create(size_t size, DSVectorMode mode, int step);
DSVector *dsv_clone(DSVector *handle); //clones adt object
void dsv_destroy(DSVector *handle);
int dsv_resize(DSVector **handle, size_t length);
boolean dsv_set(DSVector **handle, unsigned index, void * data); 
void *dsv_get(DSVector *handle, unsigned index);
int dsv_shrinkToFit(DSVector **handle);
boolean dsv_forEach(DSVector **handle, boolean (*fn_ptr)(void **));
int dsv_forEachComplex(DSVector **handle, int (*fn_ptr)(void**, void**), void **data); //pass additional 'data' arg to fn_ptr(), returns int useful as return codes, if fn_ptr returns nothing dsll_forEachComplex returns 0
void *dsv_forEachData(DSVector **handle, void *(*fn_ptr)(void**, void**), void **data);  //pass additional 'data' arg to fn_ptr(), returns void*, if fn_ptr returns nothing dsll_forEachComplex returns NULL
void **dsv_getContainer(DSVector **handle, unsigned index);
// stack functions
// should be init with: dsv_create(0, DS_VECTOR_MODE_STEP, 1);
int dsv_push(DSVector **handle, void *data); //push will put data after handle->length, use dsv_set() and dsv_forEach() to overwrite everything from start
void *dsv_pop(DSVector **handle);
int dsv_unshift(DSVector **handle, void *data);
void *dsv_shift(DSVector **handle);

void dsv_nullify(DSVector **v); //set all to null, even struct
size_t dsv_getByteSize(DSVector *v); //size of whole adt object
boolean dsv_reverse(DSVector **v);
boolean dsv_compare(DSVector *a, DSVector *b);
int dsv_areMembers(DSVector *v, void *data, unsigned start_index); //return index if found, then pass that number +1 to start_index arg to continue search
void *dsv_removeMember(DSVector **handle, unsigned idx);
int dsv_insertMember(DSVector **handle, unsigned idx, void *data);   
void dsv_swapMembers(DSVector **handle, unsigned idx_a, unsigned idx_b);
DSVector *dsv_merge(DSVector *a, DSVector *b);
void dsv_firstToLast(DSVector **handle);
void dsv_lastToFirst(DSVector **handle);
boolean dsv_isNull(DSVector *handle, unsigned idx);
int dsv_countUsed(DSVector *handle);
int dsv_countFree(DSVector *handle);

#endif
