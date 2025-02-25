# Project Name

A brief description of the project.

## Compilation (You can use your own compiler)

```sh
# Here we used GCC
gcc -c arena.c -o arena.o
```

## Example

```
#include <stdio.h>

#include "arena.h"

arena_t temp_arena          = arena_create();
arena_t some_other_arena    = arena_create();

int main() {
    // set temp arena
    arena_set_context(&temp);

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
```

for more example see the *examples* folder. This folder does not include
all possible examples. You can always consult the *arena.h* header file to 
find out about the rest of the features of the library.

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature-branch`)
3. Commit your changes (`git commit -m 'Add new feature'`)
4. Push to the branch (`git push origin feature-branch`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

