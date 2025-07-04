cmake_minimum_required(VERSION 3.28.3)
project(poker_bot)
file(GLOB SOURCES "src/*.cpp" "src/player/*.cpp" "src/deck/*.cpp" "src/equity/*.cpp" "src/evaluator/*.cpp")
add_executable(poker_bot ${SOURCES})
include_directories(include src/deck src/player src/game)
set(CMAKE_CXX_STANDARD 23)

# Enable sanitizers for debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR NOT CMAKE_BUILD_TYPE)
    message(STATUS "Enabling AddressSanitizer and UndefinedBehaviorSanitizer")
    set(SANITIZER_FLAGS "-fsanitize=address,undefined -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SANITIZER_FLAGS}")
endif()