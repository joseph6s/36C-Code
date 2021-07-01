add_library(
    insertion_sort
    insertion_sort.cpp
    utils.hpp
)

# Create a insertion sort library
target_include_directories(insertion_sort PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# This command add the include path to the target linked from insertion_sort


