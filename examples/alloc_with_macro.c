// this is the same example as arena_test.c, but using the macros
// ARENA_ALLOC(size), and ARENA_RESET() if you are bothered of adding
// NULL at the end of every function call

#include <stdio.h>
#define DEFINE_CURRCONTEXT_ALLOC
#include "arena.h"

arena_t temp_arena          = arena_create();
arena_t some_other_arena    = arena_create();

int main() {
    // set temp arena
    arena_set_context(&temp_arena);

    // allocate some things in the arena
    void* data = ARENA_ALLOC(400);
    ARENA_ALLOC(20);
    ARENA_ALLOC(43);

    // reset current arena
    ARENA_RESET();

    void* ptr = ARENA_ALLOC(400);
    // after reset the previous regions will be reused, thus same pointers
    assert(ptr == data);

    // or switch to another context    
    arena_set_context(&some_other_arena);

    // allocate some stuff in this new arena
    ARENA_ALLOC(1024);
    ARENA_ALLOC(100);
    ARENA_ALLOC(55);

    // deallocate everything in a single call
    arena_destroy(&temp_arena);
    arena_destroy(&some_other_arena);
    return 0;
}