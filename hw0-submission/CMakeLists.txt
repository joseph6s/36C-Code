cmake_minimum_required(VERSION 3.10)
# UPDATED TO 3.10 to match the cmake version on CSIF
# Defines the minimum required cmake version
# you can check cmake version on your os by typing 
# ```cmake --version``` on the terminal (#1)

project(hw0 VERSION 1.0.0)
# Project Name and Version (#2)

add_subdirectory(src)
# There is a src folder in the current directory
# this runs the setting from src/CMakeLists.txt (#->)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC insertion_sort)

# These commands link insertion_sort library to run_sort
# Note run_sort is the target, and it will have the access to the include directory defined above in target_include_directories
