
project(sqlite3-cpp CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/${CMAKE_BUILD_TYPE}/lib)

add_library(${PROJECT_NAME} SHARED
	cc_sqlite3.cc
	cc_sqlite3_exception.cc
	cc_sqlite3_blob.cc
	cc_sqlite3_type.cc
)

target_include_directories(${PROJECT_NAME} PUBLIC
	../libsqlite3/sqlite
)

target_link_libraries(${PROJECT_NAME}
	sqlite3
)
