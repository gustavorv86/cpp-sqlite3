
project(sqlite3 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/${CMAKE_BUILD_TYPE}/lib)

add_library(${PROJECT_NAME} SHARED
	sqlite/sqlite3.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
	sqlite
)

target_link_libraries(${PROJECT_NAME}
	dl
	pthread
)
