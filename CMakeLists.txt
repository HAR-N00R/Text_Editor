cmake_minimum_required(VERSION 4.1)
project(Text_Editor)

set(CMAKE_CXX_STANDARD 20)

add_executable(Text_Editor main.cpp
        TextEditor.cpp
        TextEditor.h)
