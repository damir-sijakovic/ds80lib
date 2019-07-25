#ifndef	DS_CHUNK_H
#define	DS_CHUNK_H

#define DS_CHK_NEWSTR_LIMIT 2048

typedef struct DSChunk{
    size_t size;    
    unsigned char data[1];
} DSChunk; 

void dsch_debugPrint(DSChunk *c, char *msg);
DSChunk *dsch_new(size_t size);
void dsch_set(DSChunk **handle, void *data);
DSChunk *dsch_newStr(char *str);
DSChunk *dsch_newText(char *str, size_t limit);
void *dsch_get(DSChunk *handle);
void dsch_nullify(DSChunk **handle); 
void dsch_copy(DSChunk *source, DSChunk **destination);
void dsch_resize(DSChunk **handle, size_t size);
DSChunk *dsch_join(DSChunk *a, DSChunk *b);
void dsch_destroy(DSChunk **handle);
DSChunk *dsch_split(DSChunk **original, size_t idx);
void dsch_removeRange(DSChunk **handle, size_t idx, size_t size);
void dsch_ltrim(DSChunk **handle, size_t size);
void dsch_rtrim(DSChunk **handle, size_t size);
void dsch_save(DSChunk *h, char *txtfile);      
DSChunk *dsch_load(char *txtfile);
void dsch_iterate(DSChunk **h, char *(* f)(char*) );
void dsch_iterBlocks(DSChunk **h, unsigned int block_size, void (*func)(void*));
void *dsch_find(DSChunk *arg_haystack, DSChunk *arg_needle);
boolean dsch_allowBytes(DSChunk *c, DSChunk *pattern);


#endif
