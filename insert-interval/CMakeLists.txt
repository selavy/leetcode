cmake_minimum_required(VERSION 3.5)
add_executable(insert-interval insert-interval.cpp)
target_compile_features(insert-interval PUBLIC cxx_std_17)
target_include_directories(insert-interval PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../third_party")
