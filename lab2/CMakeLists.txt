add_executable(
               sort 
               main.cpp 
               include/sort.h src/sort.cpp 
               )
               
target_include_directories(sort PRIVATE include)
