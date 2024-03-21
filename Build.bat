IF NOT EXIST "build/" mkdir build

cmake . -Bbuild/
cmake --build ./build
