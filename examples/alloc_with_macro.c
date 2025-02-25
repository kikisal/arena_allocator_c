#include <stdio.h>
// You can define this macro to define
// ARENA_ALLOC and ARENA_RESET macros
// in your code, which will allow you to do 
// arena operations on the current bound context
// without always having to put NULL at the end of
// every ARENA_ALLOC() call.
#define DEFINE_CURRCONTEXT_ALLOC
#include "arena.h"


arena_t temp               = arena_create();
arena_t some_other_arena   = arena_create();


int main() {
    arena_set_context(&temp);
    
    void* data = ARENA_ALLOC(400);
    printf("%p\n", data);

    ARENA_RESET();

    data = ARENA_ALLOC(400);
    printf("%p\n", data);

    data = ARENA_ALLOC(400);
    printf("%p\n", data);


    arena_destroy(&temp);
    arena_destroy(&some_other_arena);

    return 0;
}