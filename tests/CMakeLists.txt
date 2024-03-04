include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(lab1_test lab1_test.cpp ../lab1/include/lab1.h ../lab1/src/lab1.cpp)
target_link_libraries(lab1_test PRIVATE GTest::GTest)
target_include_directories(lab1_test PRIVATE ../lab1/include)

add_executable(lab2_test lab2_test.cpp ../lab2/include/sort.h ../lab2/src/sort.cpp)
target_link_libraries(lab2_test PRIVATE GTest::GTest)
target_include_directories(lab2_test PRIVATE ../lab2/include)

add_executable(lab3_test lab3_test.cpp ../lab3/include/lab3.h ../lab3/src/lab3.cpp ../lab3/src/shared_memory.cpp)
target_link_libraries(lab3_test PRIVATE GTest::GTest)
target_include_directories(lab3_test PRIVATE ../lab3/include)

add_executable(lab4_lib1_test lab4_lib1_test.cpp ../lab4/include/lib.h ../lab4/include/utils.h)
target_link_libraries(lab4_lib1_test GTest::gtest GTest::gtest_main lib1_static)
target_include_directories(lab4_lib1_test PRIVATE ../lab4/include)

add_executable(lab4_lib2_test lab4_lib2_test.cpp ../lab4/include/lib.h ../lab4/include/utils.h)
target_link_libraries(lab4_lib2_test GTest::gtest GTest::gtest_main lib2_static)
target_include_directories(lab4_lib2_test PRIVATE ../lab4/include)

add_executable(lab5_7_test lab5_7_test.cpp ../lab5_7/include/topology.h ../lab5_7/include/node.h ../lab5_7/include/socket.h
../lab5_7/src/client_util.cpp)
target_link_libraries(lab5_7_test GTest::gtest GTest::gtest_main zmq zmqsocket zmqnode)
target_include_directories(lab5_7_test PRIVATE ../lab5_7/include)

add_test(lab1_test lab1_test)
add_test(lab2_test lab2_test)
add_test(lab3_test lab3_test)
add_test(lab4_lib1_test lab4_lib1_test)
add_test(lab4_lib2_test lab4_lib2_test)
add_test(lab5_7_test lab5_7_test)
