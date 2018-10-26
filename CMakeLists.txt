cmake_minimum_required(VERSION 3.12)
project(musiXmatch)

set(CMAKE_CXX_STANDARD 14)

add_executable(musiXmatch main.cpp Song.cpp Song.h Songs.cpp Songs.h)