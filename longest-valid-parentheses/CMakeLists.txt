cmake_minimum_required(VERSION 3.5)
add_executable(parens parens.cpp)
target_compile_features(parens PUBLIC cxx_std_17)
target_include_directories(parens PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../third_party")
