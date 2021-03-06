﻿cmake_minimum_required (VERSION 3.1)

project ("CXX-Lectures" CXX)

# Включение высокого уровня предупреждений
if(MSVC) # Компилятор MSVC /W3
    if(CMAKE_C_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
    endif()
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_options(/experimental:external /external:anglebrackets /external:W0)
elseif(CMAKE_COMPILER_IS_GNUCC) # Компилятор GCC
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wconversion -Wextra -Wpedantic")
endif()

add_subdirectory("lecture-01-methods-ctors")
add_subdirectory("lecture-03-exception_safety-operators")
add_subdirectory("lecture-04-dtor-raii-rule_of_three")
add_subdirectory("lecture-05-move")
add_subdirectory("lecture-06-iterators")
add_subdirectory("lecture-07-sort")
add_subdirectory("lecture-08-hashtables")
add_subdirectory("lecture-09-trees")
add_subdirectory("lecture-10-avl")
add_subdirectory("lecture-11-graph")
add_subdirectory("lecture-12-dijkstra")
add_subdirectory("lecture-13-inheritance")
add_subdirectory("lecture-14-parallel")
add_subdirectory("lecture-15-qt-widgets")
add_subdirectory("lecture-16-qt-network")

add_subdirectory("practice-01-const-static-ref-namespaces-exceptions")
add_subdirectory("practice-02-template_functions")
add_subdirectory("practice-03-vector-list")
