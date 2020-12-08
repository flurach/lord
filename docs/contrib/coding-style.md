# coding style

i need this, because i started to get overburdened by the amount of code this
thing started to produce, well, i started to produce.

if not stated otherwise below, lord uses [the linux kernel coding style](https://www.kernel.org/doc/html/v4.10/process/coding-style.html).


## file structure
1. use that editorconfig file even if you can't for some reason.
2. surround header files with `#ifndef` blocks.
3. all source files except `src/lord.c` must have a corresponding header file.


## variables & macros
1. don't use UPPERCASE letters in `vars`.
2. don't use lowercase letters in `MACROS`.
3. don't use globals unless they're constant.


## structs
1. typedef and make it `CamelCase`.
2. if it's a class, comment that it is.
3. methods: `MyStruct_method(MyStruct *self, ...)`.


## enums
1. typedef and make it `CamelCase`.
2. prefix values with a `{unique letter}_{value}`, all uppercase.
3. use `X macros`, this allows for:
	- macro driven automatic code generation.
	- stringifying enums for debugging.
	- generally, good code.


## curly braces
1. omit them however you like.
