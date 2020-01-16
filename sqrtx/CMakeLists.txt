cmake_minimum_required(VERSION 3.5)
add_executable(sqrtx sqrtx.cpp)
target_compile_features(sqrtx PUBLIC cxx_std_17)
target_include_directories(sqrtx PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../third_party")
