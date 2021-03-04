include(GNUInstallDirs)

#
# LIBRARIES
#

add_executable(model_obj model_obj.cc getopt.c)
add_executable(image_bmp image_bmp.cc getopt.c)
add_executable(image_tga image_tga.cc getopt.c)

target_link_libraries(model_obj PRIVATE shape_core)
target_link_libraries(image_bmp PRIVATE shape_core)
target_link_libraries(image_tga PRIVATE shape_core)