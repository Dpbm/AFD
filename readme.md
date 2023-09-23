# AFD exercise
## A software written in C to generate and test `Deterministic finite automaton`. 

This project is a homework for the `formal languages and automatons` subject, the idea here is to transcribe the general idea of 
automatons into software.
There weren't any constraints for it, just use a lanaguage and implement a software that gets an automaton as input, and test sequences of
symbols, saying if does it'is accepted or not.

For this project, we used the c programming language. For the automatons we used some `strcuts` and `pointers` to map them. we've chosen 
that approach because it's easier to test the sequences later.

## Running

To execute this project, first compile all the `c` source files. For that you'll need 
a compiler, like `GCC` or `CLANG`. Here's an example:

```bash

gcc automaton.c afd.c utils.c

# or

gcc *.c
```

Then run the output binary, like:

```bash
./a.out

#or 

./a.exe
```
