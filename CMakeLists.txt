cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
project (Sailer)

file(GLOB_RECURSE source_list "src/*.cpp" "src/*.h")
add_executable(Sailer ${source_list})
