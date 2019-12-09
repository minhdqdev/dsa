

## Header file
A header file is a file with extension .h which contains C function declarations and macro definitions to be shared between serveral source fiels.

https://www.tutorialspoint.com/cprogramming/c_header_files.htm

A simple practice in C or C++ programs is that we keep all the const, macros, ssytem wide global variables, and function protottypes in the header fiels and include that header file wherever it is required.

### Include syntax
```
#include <file>
```

It searches for a file named 'file' in a standard list of system directories. you can prepend directories to this list with -l option while compiling your source code.

```
#include "file"
```

### Once-only headers
If a header file happens to be included twice, the compiler will process its contents twice and it will result in a error. 

The standard way to prevent this is to enclose the entire real contents of the file in a conditional, like this

```
#ifndef HEADER_FILE
#define HEADER_FILE

the entire header file file

#endif
```

### Computed includes