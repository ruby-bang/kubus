# kubus (beta)

ini adalah game pertualangan dengan tujuan untuk mencari kubus pink yang dimana itu adalah kekasihnya.

## Build
Usage:
```bash
 make <Option> [Parameter]
```

Option: 
- help    : to show usage Example
- build   : to Build with default CLIB and CINC
- clean     : to clean
everything

Parameter:
- CLIB : path to
raylib lib
- CINC : path to raylib
include
- target : to specify
path target

Advance:
  ```bash
make build CLIB="path/to/lib" CINC="path/to/include" target="path/to/target"
```

## Need*
- [raylib](https://github.com/raysan5/raylib)
- [LLVM (clang)](https://apt.llvm.org/)
