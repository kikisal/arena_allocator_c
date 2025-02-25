# Project Name

A brief description of the project.

## Compilation (You can use your own compiler)

```sh
# Clone the repository
gcc -c arena.c -o arena.o
```

## Example

```
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

