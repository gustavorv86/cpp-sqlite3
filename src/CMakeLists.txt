
cmake_minimum_required(VERSION 3.0)

project(cpp-sqlite3)

add_compile_options(-Wall -Wextra)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

add_subdirectory(libsqlite3)
add_subdirectory(libsqlite3-cpp)
add_subdirectory(main)

