add_executable(lab3 
               main.cpp 
               include/lab3.h src/lab3.cpp 
               include/utils.h
               include/shared_memory.h src/shared_memory.cpp 
               )

add_executable(child_lab3
               src/child.cpp
               include/utils.h
               include/shared_memory.h src/shared_memory.cpp 
               )

target_include_directories(lab3 PRIVATE include)
target_include_directories(child_lab3 PRIVATE include)

add_dependencies(lab3 child_lab3)