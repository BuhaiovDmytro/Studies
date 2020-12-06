cmake_minimum_required(VERSION 2.8.12)

project(SQL_ORM_Client)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

find_package(ODB REQUIRED COMPONENTS boost pgsql OPTIONAL_COMPONENTS qt sqlite)
include(${ODB_USE_FILE})

set(OdbCMake_SOURCES
	driver.cpp
	database.h
		submenu.cpp
		submenu.h
		server_context.h)

set(OdbCMake_ODB_HEADERS
		orm_classes.h)

odb_compile(OdbCMake_SOURCES FILES ${OdbCMake_ODB_HEADERS} DB pgsql
		GENERATE_QUERY GENERATE_SESSION STANDARD c++11 PROFILE boost/date-time)

add_executable(SQL_ORM_Client
	${OdbCMake_SOURCES}
	${OdbCMake_ODB_HEADERS})
target_link_libraries(SQL_ORM_Client
	${ODB_LIBRARIES})
target_include_directories(SQL_ORM_Client
	PRIVATE
		${ODB_INCLUDE_DIRS}
		${ODB_COMPILE_OUTPUT_DIR})
target_compile_definitions(SQL_ORM_Client
	PRIVATE
		DATABASE_PGSQL)
