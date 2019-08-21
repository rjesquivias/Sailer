cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
project (SailerTest)

# Recursively store all cpp files in the source_list variable
file(GLOB_RECURSE source_list "src/*.cpp")
add_executable(SailerTest ${source_list})

# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
find_package( GTest REQUIRED )      

# adds the gtest include directory
include_directories( ${GTEST_INCLUDE_DIRS} )

# links gtest
target_link_libraries( SailerTest ${GTEST_LIBRARIES} )