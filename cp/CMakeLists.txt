add_executable(main
               main.cpp 
               include/mck-k.h include/pow_of_two_allocator.h src/mck-k.cpp src/pow_of_two_allocator.cpp
               )

target_include_directories(main PRIVATE include)