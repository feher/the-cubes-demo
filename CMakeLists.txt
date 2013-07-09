cmake_minimum_required (VERSION 2.6)
project (TheCubes)

find_package(OpenGL REQUIRED)

add_subdirectory (3rdparty)

# On Visual 2005 and above, this module can set the debug working directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/3rdparty/rpavlik-cmake-modules-1c73e35")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

include_directories(
	3rdparty/glfw-2.7.6/include/
	3rdparty/glm-0.9.4.0/
	3rdparty/glew-1.9.0/include/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	GLFW_276
	GLEW_190
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

add_executable(thecubes
	src/actioncube.cpp
	src/camera.cpp
	src/compass.cpp
	src/compassdata.cpp
	src/compasslabel.cpp
	src/compasslabeldata.cpp
	src/compasslabelprogram.cpp
	src/compassprogram.cpp
	src/cube.cpp
	src/cubedata.cpp
	src/cubeprogram.cpp
	src/file.cpp
	src/geom.cpp
	src/grid.cpp
	src/griddata.cpp
	src/gridprogram.cpp
	src/main.cpp
	src/modelcube.cpp
	src/object.cpp
	src/objectprogram.cpp
	src/pointlight.cpp
	src/rglfw.cpp
	src/shader.cpp
	src/shaderprogram.cpp
	src/thecubes.cpp
	src/viewport.cpp
)
target_link_libraries(thecubes
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(thecubes PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/")
create_target_launcher(thecubes WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/")



SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )


if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
add_custom_command(
   TARGET thecubes POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/thecubes${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/src/"
)

elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

