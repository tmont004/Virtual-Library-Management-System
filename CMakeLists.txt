cmake_minimum_required(VERSION 3.30)

set(This Example)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
    BinarySearchTree.h
    Book.h 
    bookdatabase.h
    BinarySearchTree.h 
    json.hpp 
    LibrarySystem.h 
    queue.h 
    security.h 
    user_system.hpp 
)

set(Sources 
    BinarySearchTree.cpp 
    Book.cpp
    bookdatabase.cpp
    BinarySearchTree.cpp
    LibrarySystem.cpp
    queue.cpp
    security.cpp
    user_system.cpp
    main.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)