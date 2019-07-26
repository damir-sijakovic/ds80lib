#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include "../include/dslib.h"
#include "../include/chunk.h"

void dsch_debugPrint(DSChunk *c, char *msg){
    printf("== ChUNK DEBUG ========== %s\n", msg);
    printf("Chunk size: %d\n", c->size);
    printf("Chunk size: %s\n", c->data);
    printf("== END CHUNK DEBUG ========== %s\n", msg);    
}

int main(){
    
    DSChunk *c = dsch_new(100);
    printf("%d\n", 223);

    dsch_set(&c, "alphsbetagammadelta");

    

    dsch_debugPrint(dsch_newStr("Hello"), "test");

}
