cmake_minimum_required(VERSION 3.5)
add_executable(wildcard wildcard.cpp)
target_compile_features(wildcard PUBLIC cxx_std_17)
target_include_directories(wildcard PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../third_party")
