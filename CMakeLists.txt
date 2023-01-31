cmake_minimum_required(VERSION 3.21)
project(balanced_binary_search_tree)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/avl_tree)

add_executable(balanced_binary_search_tree
        src/avl_tree/avl_tree.h
        src/avl_tree/avl_tree.cpp
        src/examples/use_case_one.cpp src/examples/use_case_two.cpp)
