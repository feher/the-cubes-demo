cmake_minimum_required (VERSION 2.6)
project (TheCubes)

find_package(OpenGL REQUIRED)

add_subdirectory(3rdparty)

# On Visual Studio 2005 and above, this module can set the debug working directory.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/3rdparty/rpavlik-cmake-modules-1c73e35")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile)

include_directories(
 3rdparty/glfw-3.0.1/include/
 3rdparty/glm-0.9.4.4/
 3rdparty/glew-1.9.0/include/
 .
)

set(ALL_LIBS
 ${OPENGL_LIBRARY}
 glfw
 glew_190
)

add_definitions(
 -DTW_STATIC
 -DTW_NO_LIB_PRAGMA
 -DTW_NO_DIRECT3D
 -DGLEW_STATIC
 -D_CRT_SECURE_NO_WARNINGS
)

add_executable(thecubes
 src/actionobject.cpp
 src/camera.cpp
 src/compass.cpp
 src/compassdata.cpp
 src/compasslabel.cpp
 src/compassprogram.cpp
 src/cubedata.cpp
 src/cursor.cpp
 src/file.cpp
 src/filetga.cpp
 src/frametimer.cpp
 src/geom.cpp
 src/grid.cpp
 src/griddata.cpp
 src/gridprogram.cpp
 src/labeldata.cpp
 src/labelprogram.cpp
 src/lighttextureprogram.cpp
 src/lighttextureshadowprogram.cpp
 src/main.cpp
 src/modelobject.cpp
 src/object.cpp
 src/pointlight.cpp
 src/program.cpp
 src/shader.cpp
 src/shaderprogram.cpp
 src/shadowmap.cpp
 src/shadowmapprogram.cpp
 src/shadowmapview.cpp
 src/shadowmapviewprogram.cpp
 src/spheredata.cpp
 src/thecubes.cpp
 src/trianglemeshdata.cpp
 src/trianglemeshobject.cpp
 src/viewport.cpp
)

target_link_libraries(thecubes
 ${ALL_LIBS}
)

if (CMAKE_COMPILER_IS_GNUCXX)
 set(CMAKE_CXX_FLAGS "-std=c++11")
 target_link_libraries(thecubes ${GLFW_LIBRARIES})
endif (CMAKE_COMPILER_IS_GNUCXX)

# Xcode and Visual Studio working directories
set_target_properties(thecubes PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/")
create_target_launcher(thecubes WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/")

if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode")
 add_custom_command(
  TARGET thecubes POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/thecubes${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/src/"
 )
endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode")
