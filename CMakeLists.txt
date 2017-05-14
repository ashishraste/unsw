cmake_minimum_required(VERSION 2.8.3)
project(unsw)

add_definitions(-std=c++11)

find_package(Boost REQUIRED system filesystem thread chrono iostreams)
include_directories(include ${Boost_INCLUDE_DIRS})

add_executable(string_generator src/string_generator.cpp)
target_link_libraries(string_generator ${Boost_LIBRARIES})

add_executable(string_processor src/string_processor.cpp)
target_link_libraries(string_processor ${Boost_LIBRARIES})