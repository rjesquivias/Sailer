cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 17)
project (Sailer)

file(GLOB_RECURSE source_list "src/main.cpp" "src/Generic/*.cpp" "src/Generic/*.h")
add_executable(Sailer ${source_list})
