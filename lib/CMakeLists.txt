include(GNUInstallDirs)

#
# LIBRARIES
#

add_library(shape_core STATIC
	base_camera.cc
	base_image.cc
	base_image_bmp.cc
	base_image_tga.cc
	base_model.cc
	base_model_obj.cc
	#asset_model_reader.cc
	#asset_model_writer.cc
	#asset_sound.cc
	base.cc
	#base_reader.cc
	base_stream.cc
	#base_writer.cc
	type.cc)

add_library(shape_core_video STATIC
	video_gl_glad.c
	video_gl_base_device.cc
	video_gl_base_render_buffers.cc
	video_gl_base_shader.cc
	video_gl_base_shader_program.cc
	video_gl_base_texture.cc
	video_gl_base_model.cc
	video_gl_base_model_params.cc
	video_gl_base_model_vertex.cc)

target_include_directories(shape_core PUBLIC $<INSTALL_INTERFACE:include> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_include_directories(shape_core_video PUBLIC $<INSTALL_INTERFACE:include> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_compile_features(shape_core       PUBLIC cxx_std_20)
target_compile_features(shape_core_video PUBLIC cxx_std_20)

target_link_libraries(shape_core_video PRIVATE shape_core)

#
# INSTALL
#

install(TARGETS shape_core EXPORT core COMPONENT core-libraries
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(TARGETS shape_core_video EXPORT core_video COMPONENT core-video-libraries
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES
	asset_image.hh
	asset_model.hh
	asset_model_reader.hh
	asset_model_writer.hh
	asset_sound.hh
	base.hh
	io_reader.hh
	io_writer.hh
	math_affine.hh
	math_quaternion.hh
	math_simd_arm.hh
	math_simd_sse.hh
	math_vector.hh
	type.hh DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT core-headers)

install(FILES
	video_gl_glad.h
	video_gl_khrplatform.h
	video_gl_base_device.hh
	video_gl_base_framebuffer.hh
	video_gl_base.hh
	video_gl_base_shader_buffers.hh
	video_gl_base_shader.hh
	video_gl_base_shader_program.hh
	video_gl_base_shader_textures.hh
	video_gl_base_texture.hh
	video_gl_base_vertex_buffer.hh
	video_gl_base_vertex.hh DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT video-headers)

install(EXPORT core
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake NAMESPACE shape:: FILE shape_core_targets.cmake)

install(EXPORT core_video
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake NAMESPACE shape:: FILE shape_core_targets.cmake)