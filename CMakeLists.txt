cmake_minimum_required(VERSION 3.20)

project(os_labs C CXX)

enable_testing()

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include(FindThreads)

add_subdirectory(lab1)
add_subdirectory(lab2)

add_subdirectory(tests)