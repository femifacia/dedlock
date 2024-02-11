# Dedlock

## Goal of the project

The goal of this project is to implement a **lockscreen** with dedsec theme.
When you launch the **dedlock** binary, your screen is locked until you type your password followed by ENTER.
Don't wait for a fancy prompt to appear and tell you the number of character typed.

Just enter your password to unlock the screen

**Warning**

This project is not finished. We are looking for a low level way to maintain the top level frame before
adding other UI elements.

## Os supported

- Linux

## Requirement

### On Linux

* g++
* Conan 
* CMake 3.17

## HOW TO COMPILE

### On Linux

    mkdir build && cd build && conan install .. && cmake ../ -G 'Unix Makefiles' && cmake –build . && make

## HOW TO EXECUTE

### On Linux

After the compilation, on the root of the repository

Type this

    ./build/bin/dedlock

After this, just type your password to unlock your screen
