cmake_minimum_required(VERSION 3.1)
project(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    enemyClass.h
    main.cpp
    mainHeader.h
    playerClass.h)

add_executable(src ${SOURCE_FILES})