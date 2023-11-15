add_executable(lab1 
               main.cpp 
               include/lab1.h src/lab1.cpp 
               )

add_executable(child
               src/child.cpp
               )

target_include_directories(lab1 PRIVATE include)

add_dependencies(lab1 child)