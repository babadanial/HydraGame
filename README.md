# HydraGame

Welcome!
This repository contains the contents of the HydraGame project written by Daniel Akbarzadeh.

---
### Project Files
This folder contains the implementations and interface files of all the classes that make up the final executable, as well as a client that handles inputs (game commands). 

A Makefile is also included to allow easy compilation of the project. This Makefile provides many debugging-friendly flags to the compiler so as to allow extensive debugging of the program in GDB, as well as memory leak and other checks using Valgrind.

### Test Files
This folder contains the test suite for this project, contained within the suite*.txt file. They consist of black-box, functional tests which are also used as regression tests. They were also supplemented with more information once white-box-level knowledge of the program was available after its implementation, as I was actively looking for ways to break my own code. The files ending in .in and .out for each test case will likely be of most interest to you: they contain the inputs and expected outputs for each case, respectively.
