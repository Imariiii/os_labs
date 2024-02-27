add_executable(
               cp
               main.cpp 
               include/pow_allocator.h src/pow_allocator.c 
               include/mck_allocator.h src/mck_allocator.c 
               )
               
target_include_directories(cp PRIVATE include)
target_link_libraries(cp m)