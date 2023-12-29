cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lab1_bitarray)

set(TEST_NAME tests/testlist.cpp)

if (MSVC)

    add_compile_options(/W4 /WX)

else ()

    add_compile_options(-Wall -Wextra -pedantic -Werror)

endif ()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/116b7e55281c4200151524b093ecc03757a4ffda.zip
)
FetchContent_MakeAvailable(googletest)

add_library(
  bit_array STATIC
  bit_array.cpp
  bit_array.h
  )

add_executable(${PROJECT_NAME} ${TEST_NAME})

target_link_libraries(${PROJECT_NAME} bit_array GTest::gtest_main)

enable_testing()

include(GoogleTest)

gtest_discover_tests(${PROJECT_NAME})