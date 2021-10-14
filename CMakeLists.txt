cmake_minimum_required(VERSION 2.8)
project(desktop72_project CXX)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-lpthread")
SET(CMAKE_CXX_STANDARD 14)

add_subdirectory(desktop72)
