cmake_minimum_required(VERSION 3.16)
project(BlackjackGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

file(GLOB SOURCES src/*.cpp)
add_executable(blackjack ${SOURCES})
