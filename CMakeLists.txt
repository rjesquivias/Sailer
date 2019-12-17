cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 17)
project (Sailer)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/test/findGmock)

# Recursively store all cpp files in the source_list variable
file(GLOB_RECURSE source_list "src/*.cpp")

add_executable(Sailer ${source_list})
