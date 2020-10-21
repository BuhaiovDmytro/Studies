cmake_minimum_required(VERSION 3.17)
project(Lab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab2 main.cpp db_operations.h db_operations.cpp psql_getters.cpp psql_getters.h submenu.cpp submenu.h)

find_package(PostgreSQL REQUIRED)

target_link_libraries(Lab2 PRIVATE PostgreSQL::PostgreSQL)