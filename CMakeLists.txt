cmake_minimum_required(VERSION 3.0)

project(shape.core)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SHAPE_CORE
	base.hh
	base.cc
	asset/reader/model.hh
	asset/reader/model.cc
	asset/writer/model.hh
	asset/writer/model.cc
	asset/image.hh
	asset/image.cc
	asset/model.hh
	asset/model.cc
	asset/model_buffer.hh
	asset/model_buffer.cc
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
	video/base/framebuffer.hh
	video/base/framebuffer.cc
	video/base/shader.hh
	video/base/shader.cc
	video/base/shader_buffers.hh
	video/base/shader_buffers.cc
	video/base/shader_program.hh
	video/base/shader_program.cc
	video/base/shader_textures.hh
	video/base/shader_textures.cc
	video/base/texture.hh
	video/base/texture.cc
	video/base/vertex.hh
	video/base/vertex.cc
	video/base/vertex_buffer.hh
	video/base/vertex_buffer.cc)

set(SHAPE_CORE_VIDEO_COMPONENTS
	video/components/camera.hh
	video/components/camera.cc)

add_library(shape.core STATIC
	${SHAPE_CORE}
	${SHAPE_CORE_VIDEO_GLAD}
	${SHAPE_CORE_VIDEO_BASE}
	${SHAPE_CORE_VIDEO_COMPONENTS})