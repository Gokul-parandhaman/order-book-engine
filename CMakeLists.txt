cmake_minimum_required(VERSION 3.16)
project(order_book_engine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_library(order_book src/order_book.cpp)
target_include_directories(order_book PUBLIC src)

add_executable(obe_main src/main.cpp)
target_link_libraries(obe_main PRIVATE order_book)

enable_testing()
add_executable(obe_tests tests/test_order_book.cpp)
target_link_libraries(obe_tests PRIVATE order_book)
add_test(NAME obe_tests COMMAND obe_tests)
