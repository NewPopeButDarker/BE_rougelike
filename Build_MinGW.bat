IF NOT EXIST "build/" mkdir build

cmake . -Bbuild/ -G "MinGW Makefiles"
cmake --build ./build
