# BE_rougelike

## Overview

## Build

### :page_facing_up: Requirements
This project can be run **only on windows**.  

To build it you will need CMake and C compiler with build system of your choice.  

If you don't know what was said in previous line or don't know how to do it read next sections.  
If you know how to use cmake then just clone this project and build it :)  

Next section describes how to download everything you need to build this project using MSYS. If you want to use something different than MSYS - it won't be covered here so just look it up :)

### :gear: Example requirements setup (using MSYS2)
1. To start download MSYS from [their website](https://www.msys2.org/) or [github](https://github.com/msys2/msys2-installer/releases).  
2. Enter MSYS instalation directory and run terminal app from [enviroment](https://www.msys2.org/docs/environments/) of your choice (MSYS/MinGW64/ucrt64).
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
       
5. Add your enviroment bin directory to path [like this](https://helpdeskgeek.com/windows-10/add-windows-path-environment-variable/)  
  path should look something like this: _X:<msys_path>/<your_enviroment>/bin_  
  e.g. path for ucrt64 enviroment:  
  _C:\msys64\ucrt64\bin_  
7. Open cmd (Press win+R, type cmd and press enter).
8. In command window type:
   ```console
   $ gcc --version
   ```
   Press enter and you should see something like this:
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

If you followed steps from Example requirements setup section replace "<your_generator>" with either "Ninja", "MinGW Makefiles" or "MSYS Makefiles" depending on what you've chosen.  
If you didn't followed those steps then you probably know what you should do :)  
 
```console
$ mkdir build
$ cd .\build\
$ cmake .. -G "<your_generator>"
$ cmake --build . 
```
