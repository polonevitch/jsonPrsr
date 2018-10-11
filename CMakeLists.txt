cmake_minimum_required(VERSION 2.8)
project(jsonPrsr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_library (${PROJECT_NAME} parser.cpp parser.h json.hpp)
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

add_executable (cTest test.c)
target_link_libraries(cTest ${PROJECT_NAME})
set_target_properties(cTest PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

#add_executable (${PROJECT_NAME} test.c json.hpp parser.cpp)
#set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")