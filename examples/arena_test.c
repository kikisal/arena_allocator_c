#include <stdio.h>

#include "arena.h"

arena_t temp_arena          = arena_create();
arena_t some_other_arena    = arena_create();

int main() {
    // set temp arena
    arena_set_context(&temp_arena);

    // allocate some things in the arena
    void* data = arena_alloc(400, NULL);
    arena_alloc(20, NULL);
    arena_alloc(43, NULL);

    // reset current arena
    arena_reset(NULL);

    void* ptr = arena_alloc(400, NULL);
    // after reset the previous regions will be reused, thus same pointers
    assert(ptr == data);

    // or switch to another context    
    arena_set_context(&some_other_arena);

    // allocate some stuff in this new arena
    arena_alloc(1024, NULL);
    arena_alloc(100, NULL);
    arena_alloc(55, NULL);

    // deallocate everything in a single call
    arena_destroy(&temp_arena);
    arena_destroy(&some_other_arena);
    return 0;
}