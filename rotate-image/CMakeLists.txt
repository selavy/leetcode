cmake_minimum_required(VERSION 3.5)
add_executable(rotate rotate.cpp)
target_compile_features(rotate PUBLIC cxx_std_17)
target_include_directories(rotate PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../third_party")
