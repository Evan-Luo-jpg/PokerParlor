cmake_minimum_required(VERSION 3.28.3)
project(poker_bot)
file(GLOB SOURCES "src/*.cpp" "src/player/*.cpp" "src/deck/*.cpp")
add_executable(poker_bot ${SOURCES})
include_directories(include src/deck src/player src/game)
set(CMAKE_CXX_STANDARD 23)