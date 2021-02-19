cmake_minimum_required (VERSION 3.0)

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

add_subdirectory("practice-01-const-static-ref-namespaces-exceptions")
add_subdirectory("practice-02-template_functions")
add_subdirectory("practice-03-vector")
