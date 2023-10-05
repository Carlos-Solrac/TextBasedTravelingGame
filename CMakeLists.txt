cmake_minimum_required(VERSION 3.21)
project(Assigment8)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assigment8
        BadGuy.cpp
        BadGuy.h
        PlayerList.cpp
        PlayerList.h
        Rooms.cpp
        Rooms.h
        SuperUser.cpp
        SuperUser.h
        TextBasedGamePart8.cpp
        Users.cpp
        Users.h)
