cmake_minimum_required(VERSION 3.27)
project(lod_server_test_1)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.65.0 REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(lod_server_test_1 main.cpp)

# Link Boost libraries
target_link_libraries(lod_server_test_1 ${Boost_LIBRARIES})
