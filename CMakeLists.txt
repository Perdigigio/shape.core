cmake_minimum_required(VERSION 3.0)

project(shape.core)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SHAPE_CORE
	base.hh
	base.cc)

set(SHAPE_CORE_STREAM
	stream/reader.cc
	stream/reader.hh
	stream/writer.cc
	stream/reader.hh)

add_library(shape.core STATIC
	${SHAPE_CORE}
	${SHAPE_CORE_STREAM})

add_executable(test test.cc)

target_link_libraries(test shape.core)