cmake_minimum_required(VERSION 3.27)
project(json_parser)

set(CMAKE_CXX_STANDARD 20)

#add_executable(json_parser_runner
#        src/main.cpp
#        src/JsonElement.h
#        src/JsonElement.cpp
#        src/JsonParser.h
#        src/JsonParser.cpp)

add_library(
        json_parser
        SHARED
        src/JsonElement.h
        src/JsonElement.cpp
        src/JsonParser.h
        src/JsonParser.cpp
)

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

add_executable(
        json_parser_test
        test/JsonParserTest.cpp
)
target_include_directories(json_parser_test PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(
        json_parser_test
        GTest::gtest_main
        json_parser
)

include(GoogleTest)
gtest_discover_tests(json_parser_test)
