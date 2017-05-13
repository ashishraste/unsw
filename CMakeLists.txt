cmake_minimum_required(VERSION 2.8.3)
project(unsw)

add_definitions(-std=c++11)

find_package(Boost REQUIRED system filesystem thread chrono)
include_directories(include ${Boost_INCLUDE_DIRS})

add_executable(something src/something.cpp)
target_link_libraries(something ${Boost_LIBRARIES})