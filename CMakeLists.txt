cmake_minimum_required(VERSION 3.0)

project(shape.core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SHAPE_CORE
	base.hh
	base.cc
	asset/image.hh
	asset/image.cc
	asset/model.hh
	asset/model.cc
	asset/sound.hh
	asset/sound.cc
	io/reader.hh
	io/reader.cc
	io/writer.hh
	io/writer.cc)

set(SHAPE_CORE_VIDEO_GLAD
	video/glad/glad.h
	video/glad/glad.c)

set(SHAPE_CORE_VIDEO_BASE
	video/base/device.hh
	video/base/device.cc
	video/base/shader.hh
	video/base/shader.cc
	video/base/shader_program.hh
	video/base/shader_program.cc
	video/base/vertex.hh
	video/base/vertex.cc)

add_library(shape.core STATIC
	${SHAPE_CORE}
	${SHAPE_CORE_VIDEO_GLAD}
	${SHAPE_CORE_VIDEO_BASE})

add_executable(test test.cc)

target_link_libraries(test shape.core opengl32)