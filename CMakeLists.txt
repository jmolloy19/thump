cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(StockWatch)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_compile_options(-Wall -Wextra -pedantic)
add_compile_definitions(STOCKWATCH_MIGRATIONS_DIR="${PROJECT_SOURCE_DIR}/src/stockwatch/postgres/migrations/")
add_compile_definitions(STOCKWATCH_JSONS_DIR="${PROJECT_SOURCE_DIR}/jsons/")

add_subdirectory(src)

option(Test "Build Debugging Tests" OFF)
if(Test)
    add_subdirectory(test)
endif()
