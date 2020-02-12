cmake_minimum_required(VERSION 3.5)
add_executable(merge-intervals merge-intervals.cpp)
target_compile_features(merge-intervals PUBLIC cxx_std_17)
target_include_directories(merge-intervals PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../third_party")
