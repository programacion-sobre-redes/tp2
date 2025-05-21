cmake_minimum_required(VERSION 3.14)
project(tp2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  tp_tests
  tests/tests.cpp
  BMPImage.cpp
)
target_link_libraries(
  tp_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tp_tests)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Main executable
add_executable(
  main
  main.cpp
  utils/utils.cpp
  BMPImage.cpp
  filters/filters.cpp
)

# Include the directory containing the header files
target_include_directories(
  main PRIVATE ${CMAKE_SOURCE_DIR}
)

# Link threads library
target_link_libraries(main PRIVATE Threads::Threads)


