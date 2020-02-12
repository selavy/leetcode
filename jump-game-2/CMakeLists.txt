cmake_minimum_required(VERSION 3.5)
add_executable(jump jump.cpp)
target_compile_features(jump PUBLIC cxx_std_17)
target_include_directories(jump PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../third_party")
