cmake_minimum_required(VERSION 3.15)
project(early)

set(CMAKE_CXX_STANDARD 14)

add_executable(early main.cpp early.cpp early.h lexer.h gramma.h lexical.cpp lexical.h early_run.cpp early_run.h parse_tree.h parse_tree.cpp)