set(INC_DIR ${CMAKE_SOURCE_DIR}/lab5_7/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/lab5_7/src)

add_library(zmqsocket STATIC ${SRC_DIR}/socket.cpp ${INC_DIR}/socket.h)
add_library(zmqnode STATIC ${SRC_DIR}/node.cpp ${INC_DIR}/node.h )

target_link_libraries(zmqnode zmqsocket)
target_include_directories(zmqsocket PRIVATE ${INC_DIR})
target_include_directories(zmqnode PRIVATE ${INC_DIR})

add_executable(client ${SRC_DIR}/client.cpp ${SRC_DIR}/client_util.cpp  ${INC_DIR}/node.h ${INC_DIR}/topology.h)
add_executable(server ${SRC_DIR}/server.cpp ${INC_DIR}/node.h)
target_include_directories(client PRIVATE ${INC_DIR})
target_include_directories(server PRIVATE ${INC_DIR})

target_link_libraries(client zmq zmqnode)
target_link_libraries(server zmq zmqnode)
target_link_libraries(zmqnode zmq)
target_link_libraries(zmqsocket zmq)
