# BE_rougelike

## Overview

## Build

### :page_facing_up: Requirements
This project can be run **only on windows**.  

To build it you will need CMake and C compiler with build system of your choice.

### 	:toolbox: Example setup (using MSYS2)
1. To start download MSYS from [their website](https://www.msys2.org/) or [github](https://github.com/msys2/msys2-installer/releases).  
2. Enter MSYS instalation folder and run terminal from [enviroment](https://github.com/msys2/msys2-installer/releases) of your choice.
3. Next install compiler, build system and cmake for your enviroment:  
   cmake
   ```console
   $ pacman -S cmake #MSYS
   $ pacman -S mingw-w64-x86_64-cmake #MinGW64
   $ pacman -S mingw-w64-ucrt-x86_64-cmake #ucrt64
   ```
   gcc
   ```console
   $ pacman -S gcc #MSYS
   $ pacman -S mingw-w64-x86_64-gcc #MinGW64
   $ pacman -S mingw-w64-ucrt-x86_64-gcc #ucrt64
   ```
   build system  
   either make
   ```console
   $ pacman -S make #MSYS
   $ pacman -S mingw-w64-x86_64-make #MinGW64
   $ pacman -S mingw-w64-ucrt-x86_64-make #ucrt64
   ```
   or ninja
   ```console
   $ pacman -S ninja #MSYS
   $ pacman -S mingw-w64-x86_64-ninja #MinGW64
   $ pacman -S mingw-w64-ucrt-x86_64-ninja #ucrt64
   ```  
       
5. Add X:<msys_path>/<your_enviroment>/bin to path [like this](https://helpdeskgeek.com/windows-10/add-windows-path-environment-variable/)  
  e.g. path for ucrt64 enviroment:  
  _C:\msys64\ucrt64\bin_  
7. Press win+R, type cmd and press enter.
8. Type
   ```console
   $ gcc --version
   ```
   You should see something like this:
   ```console
   gcc.exe (Rev5, Built by MSYS2 project) 13.2.0
   Copyright (C) 2023 Free Software Foundation, Inc.
   This is free software; see the source for copying conditions.  There is NO
   warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   ```
   If version info will show up everything should be set up correctly

### :hammer_and_wrench: Building
To build project start with creating directory and opening it in cmd  
Then git clone it using:
```console
$ git clone https://github.com/NewPopeButDarker/BE_rougelike.git .
```

Next you just need to build it using cmake.  
If you followed steps from example setup as <your_generator> use either Ninja, MinGW Makefiles or MSYS Makefiles.
 
```console
$ mkdir build
$ cd .\build\
$ cmake .. -G "<your_generator>"
$ cmake --build . 
```
