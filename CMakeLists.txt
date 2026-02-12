cmake_minimum_required(VERSION 3.16)
project(BlackjackGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

file(GLOB SOURCES src/*.cpp)
list(FILTER SOURCES EXCLUDE REGEX "src/main\\.cpp")

add_library(blackjack_lib ${SOURCES})
target_include_directories(blackjack_lib PUBLIC include)

add_executable(blackjack src/main.cpp)
target_link_libraries(blackjack PRIVATE blackjack_lib)

# ---------- GoogleTest ----------
# include(FetchContent)

# FetchContent_Declare(
#   googletest
#   GIT_REPOSITORY https://github.com/google/googletest.git
#   GIT_TAG v1.14.0
# )

# FetchContent_MakeAvailable(googletest)

# enable_testing()

# add_executable(blackjack_tests
#   tests/deck_tests.cpp
#   tests/player_tests.cpp
#   tests/blackjack_tests.cpp
# )

# target_link_libraries(blackjack_tests
#   PRIVATE
#     blackjack_lib
#     gtest_main
# )

# include(GoogleTest)
# gtest_discover_tests(blackjack_tests)
