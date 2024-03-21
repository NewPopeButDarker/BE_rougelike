# BE_rougelike

## Overview

## Build

### :page_facing_up: Requirements
This project can be built **only on windows**.  
To do this you will need [CMake](https://cmake.org/) and at least one compiler e.g.:
* [GNU Compiler Collection (MinGW)](https://www.mingw-w64.org/)
* [Clang](https://www.mingw-w64.org/)
* [MSVC](https://learn.microsoft.com/en-us/cpp/?view=msvc-170)

or any other of your choice.  

### :hammer_and_wrench: Building
If you are equipped in CMake and a compiler you need to clone this repo
```console
$ git clone https://github.com/NewPopeButDarker/BE_rougelike.git
```

**After that you are good to go!**  

Just run _Build.bat_ and project will be build using default compiler and an executable will be placed in build/bin directory  
Alternatively you can run _Build_MinGW.bat_ to compile using MingGW gcc  

Or if you want to do it manualy (or specify other building options) you can do it like this (while in project directory):  
```console
$ mkdir build
$ cd .\build\
$ cmake ..
$ cmake --build . 
```
Of course you can modify Build.bat to your liking :)
