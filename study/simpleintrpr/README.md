# Simple Interpreter

Features expected:

 - calculates equations with  - + / *
 - operator priority aware
 - parenthes aware
 - unar + and -
 - multiple equations separated by (;)
 - built-in consts (pi, e)
 - new const declaration
 - built-in functions with variable arg number
 - new function declaration


# Build & Test

```
make
```



# Roadmap

 - [x] Lexical analyzer
 - [ ] Syntax analyzer
 - [ ] Calculator (stack machine)
 - [ ] Interpreter (facade for all above components)


# Constraints

 - Language: C++ (hopefully C++14)
 - TDD: GoogleTest
 - Build: make


# Reference

 Guide (Russian): https://habrahabr.ru/post/231657/
