cmake_minimum_required(VERSION 3.5)
add_executable(missing_positive missing_positive.cpp)
target_compile_features(missing_positive PUBLIC cxx_std_17)
target_include_directories(missing_positive PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../third_party")
