#include "arena.h"

#include <stdlib.h>

#define REGION_DEFAULT_SIZE 256*1024*1024
#define REGION_ELEMENT_TYPE uintptr_t

#define ARENA_MALLOC malloc
#define ARENA_FREE   free

static arena_t* arena_context = NULL;

struct region_st {
    region_t* next;
    size_t capacity;
    size_t size;
    char data[];
}; // struct region_st
 
region_t* region_create(size_t capacity) {
    region_t* region = ARENA_MALLOC(sizeof(region_t) + capacity * sizeof(REGION_ELEMENT_TYPE));
    region->capacity = capacity;
    region->size     = 0;
    region->next     = NULL;
    
    return region;
}

#define region_destroy(region) ARENA_FREE(region)

void* arena_alloc(size_t size, arena_t* arena) {
    
    arena = arena_get_context(arena);

    if (arena == NULL)
        return NULL;

    size                  = region_compute_alloc_size(size);
    size_t alloc_capacity = size > REGION_DEFAULT_SIZE ? size : REGION_DEFAULT_SIZE; 
    
    if (arena->begin == NULL) {
        ARENA_ASSERT(arena->end == NULL);

        region_t * region = region_create(alloc_capacity);
        
        if (region == NULL)
            return NULL;
        
        arena->begin = arena->end = region;
        arena->region_count++;
    }

    region_t* curr = arena->begin;
    while (curr != NULL) {
        if (curr->size + size <= curr->capacity)
            break;
        
        curr = curr->next;
    }

    if (curr == NULL) {
        curr = region_create(alloc_capacity);

        if (curr == NULL)
            return NULL;

        arena->region_count++;

        arena->end->next = curr;
        arena->end       = curr;
    }

    void* ptr = &(curr->data[curr->size]);
    curr->size += size;
    return ptr;
}

void arena_reset(arena_t* arena) {
    arena = arena_get_context(arena);
    if (!arena) return;

    region_t* curr = arena->begin;

    while (curr != NULL) {
        curr->size = 0;
        curr       = curr->next;
    }
    
    return;
}

void arena_destroy(arena_t* arena) {
    region_t* curr = arena->begin;

    while (curr != NULL) {
        region_t* tmp = curr;
        curr = curr->next;
        region_destroy(tmp);
    }
    
    arena->begin = arena->end = NULL;
}


size_t region_compute_alloc_size(size_t size) {
    size_t m = size % sizeof(REGION_ELEMENT_TYPE);
    size    -= m;
    size     = size / sizeof(REGION_ELEMENT_TYPE);
    size     = size + (size_t) (m > 0);
    return size;
}

size_t arena_allocated_size(arena_t arena) {
    region_t* curr = arena.begin;
    size_t total = 0;
    while(curr != NULL) {
        total += curr->size;
        curr = curr->next;
    }

    return total;
}

void arena_set_context(arena_t* arena) {
    arena_context = arena;
}