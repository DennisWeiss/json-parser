cmake_minimum_required(VERSION 3.27)
project(json_parser)

set(CMAKE_CXX_STANDARD 20)

add_library(json_parser SHARED
        JsonParser.cpp
        JsonParser.h
        JsonElement.cpp
        JsonElement.h)
