#pragma once

#define PLATFORM STD_LIBC_PLATFORM

#if PLATFORM != STD_LIBC_PLATFORM
#   typedef size_t unsigned long long;
#else
#   include <inttypes.h>
#endif

#include <assert.h>

#define ARENA_ASSERT(cond) assert((cond))

// #define DEFINE_CURRCONTEXT_ALLOC

#ifdef DEFINE_CURRCONTEXT_ALLOC
#   define ARENA_ALLOC(size)  arena_alloc(size, NULL)
#   define ARENA_RESET()      arena_reset(NULL)
#endif

#define ARENA_API    extern
#define ARENA_USES_CONTEXT

#ifndef NULL
#   define NULL (void*) 0
#endif

#define arena_get_context(arena) ((arena) == NULL) ? arena_context : (arena)

typedef struct arena_st arena_t;
typedef struct region_st region_t;

struct arena_st {
    region_t* begin;
    region_t* end;
    size_t region_count;
}; // struct region_st

ARENA_API region_t* region_create(size_t capacity);
ARENA_API size_t    region_compute_alloc_size(size_t size);

/**
@info: Conventions of this library: 
    - For functions marked with ARENA_USES_CONTEXT:
        if arena is NULL, the library will use the current context arena
        set with arena_set_context(arena).
    - For any other function that is not marked with ARENA_USES_CONTEXT:
        the arena must be always specified.
*/
ARENA_USES_CONTEXT ARENA_API void*    arena_alloc(size_t size, arena_t* arena);
ARENA_USES_CONTEXT ARENA_API void     arena_reset(arena_t* arena);
ARENA_API void                        arena_destroy(arena_t* arena);
ARENA_API size_t                      arena_allocated_size(arena_t arena);
ARENA_API void                        arena_set_context(arena_t* arena);

#define arena_create() (arena_t) {.begin = NULL, .end = NULL, .region_count = 0}