# BE_rouglike project
BE_rouglike is a game about biomedical engineering student who has to fight evil biomachines to free his coleagues and professors.

## Introduction

BE_rougelike[might change] its rougelike game with rpg accents.

## Build

### Requirements
You can build this project only on windows and you are required to have at least these three things 
CMake, c compiler and build system 
You can download everything using [MSYS2](https://www.msys2.org/) 
Make sure that you added your enviroment bin directory to path!

### Downloading
Firs you have to download this project or clone it using git. 
To clone it open cmd in selected directory and use (dot in the end is important).
```console
    git clone https://github.com/NewPopeButDarker/BE_rougelike.git .
```

### Building project
To create build open project directory in cmd create build directory and enter it 
```console
    mkdir build && cd build
```

Now use cmake to build this project 
```console
    cmake ..
    cmake --build .
```
/bin directory should be created with your game in here.

## Documentation

### Requirements
To create documentation you have to install [doxygen](https://www.doxygen.nl/index.html) and add it's directory to path 

### Creating docs
If you have doxygen installed open project folder in cmd (make sure its the same directory where Doxyfile is located) and run doxygen generator: 
```console
    doxygen Doxyfile
```

/docs directory should be created with subdirectories for each format you have installed 