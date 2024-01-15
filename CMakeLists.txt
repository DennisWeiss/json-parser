cmake_minimum_required(VERSION 3.27)
project(json_parser)

set(CMAKE_CXX_STANDARD 20)

file(
        GLOB
        JSON_PARSER_SRC
        include/json_parser/*.h
        src/*.h
        src/*.cpp
)

add_library(
        json_parser
        SHARED
        ${JSON_PARSER_SRC}
)

target_include_directories(json_parser PUBLIC ${CMAKE_SOURCE_DIR}/include/json_parser)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

file(
        GLOB
        JSON_PARSER_TEST_SRC
        test/*.cpp
)

add_executable(
        json_parser_test
        ${JSON_PARSER_TEST_SRC}
)
target_include_directories(json_parser_test PUBLIC ${CMAKE_SOURCE_DIR}/include/json_parser)
target_link_libraries(
        json_parser_test
        GTest::gtest_main
        json_parser
)

include(GoogleTest)
gtest_discover_tests(json_parser_test)
