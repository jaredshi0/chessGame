cmake_minimum_required(VERSION 3.24)
project(group8project)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)
include_directories(Pieces)

add_executable(group8project
        Board.h
        main.cpp
        Piece.h
        State.h
        AI.h)
