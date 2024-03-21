cmake_minimum_required(VERSION 3.10)
project(game)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(OpenGL REQUIRED)

add_subdirectory(external/glad)

include_directories(${OPENGL_INCLUDE_DIR}
                    external/glad/include)

add_executable(game WIN32 src/main.c)

target_link_libraries(game ${OPENGL_gl_LIBRARY}
                            glad)
