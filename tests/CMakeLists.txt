cmake_minimum_required(VERSION 3.25)

project(lab3_tests)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_compile_options(--coverage)
add_link_options(--coverage)

enable_testing()

add_executable(
  app
  ../src/alu.cpp
  ../src/command.cpp
  ../src/core.cpp
  ../src/cpu.cpp
  ../src/memory.cpp
  ../src/lib.cpp
  main.cpp
)

target_link_libraries(
  app
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(app)
