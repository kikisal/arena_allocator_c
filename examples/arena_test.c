#include <stdio.h>

#include "arena.h"

arena_t temp               = arena_create();
arena_t some_other_arena   = arena_create();

int main() {
    arena_set_context(&temp);
    
    void* data = arena_alloc(400, NULL);
    printf("%p\n", data);

    arena_reset(NULL);

    data = arena_alloc(400, NULL);
    printf("%p\n", data);

    data = arena_alloc(400, NULL);
    printf("%p\n", data);


    arena_destroy(&temp);
    arena_destroy(&some_other_arena);
    return 0;
}