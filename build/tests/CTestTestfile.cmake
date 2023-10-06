# CMake generated Testfile for 
# Source directory: /home/anna/os_labs/tests
# Build directory: /home/anna/os_labs/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[lab1_test]=] "lab1_test")
set_tests_properties([=[lab1_test]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/anna/os_labs/tests/CMakeLists.txt;17;add_test;/home/anna/os_labs/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
