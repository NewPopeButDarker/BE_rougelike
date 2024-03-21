@echo off

IF NOT EXIST "build/" (
  mkdir build
  echo Created ./build/ directory.
  echo:
)

echo Generating build system files.
cmake . -Bbuild/
echo:

echo Building project.
cmake --build ./build
