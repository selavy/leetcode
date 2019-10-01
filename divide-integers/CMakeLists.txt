cmake_minimum_required(VERSION 3.5)

add_library(Flags INTERFACE)
target_compile_options(Flags INTERFACE
    -Wall
    -Werror
    -march=native
    -Wno-error=overflow
    )

add_executable(divide divide.cpp)
target_link_libraries(divide Flags)
set_target_properties(divide PROPERTIES CXX_STANDARD 17)
