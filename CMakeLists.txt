cmake_minimum_required(VERSION 3.26)
project(game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(game main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
include_directories(C:/SFML/include)
target_link_libraries(game sfml-system sfml-window sfml-graphics sfml-audio sfml-network)