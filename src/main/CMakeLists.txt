
project(sqlite3-cpp-test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/${CMAKE_BUILD_TYPE}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie")

# add_compile_options(-no-pie)

add_executable(${PROJECT_NAME} 
	main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
	../libsqlite3-cpp
)

target_link_libraries(${PROJECT_NAME}
    sqlite3
    sqlite3-cpp
)

