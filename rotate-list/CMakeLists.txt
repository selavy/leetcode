cmake_minimum_required(VERSION 3.5)
add_executable(rotate-list rotate-list.cpp)
target_compile_features(rotate-list PUBLIC cxx_std_17)
target_include_directories(rotate-list PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../third_party")
