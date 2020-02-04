cmake_minimum_required(VERSION 3.5)
add_executable(spiral spiral.cpp)
target_compile_features(spiral PUBLIC cxx_std_17)
target_include_directories(spiral PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../third_party")
