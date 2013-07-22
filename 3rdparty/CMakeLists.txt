if(MSVC AND NOT "${MSVC_VERSION}" LESS 1400)
 add_definitions( "/MP" )
endif()

add_definitions(
 -DTW_STATIC
 -DTW_NO_LIB_PRAGMA
 -DTW_NO_DIRECT3D
 -DGLEW_STATIC
 -D_CRT_SECURE_NO_WARNINGS
)

### GLEW ###

include_directories(
 glew-1.9.0/include/
)

set(GLEW_SOURCE
 glew-1.9.0/src/glew.c
)

set(GLEW_HEADERS
 glew-1.9.0/inlude/
)

add_library(glew_190 STATIC
 ${GLEW_SOURCE}
 ${GLEW_INCLUDE}
)

target_link_libraries(glew_190
 ${OPENGL_LIBRARY}
 ${EXTRA_LIBS}
)

### GLFW ###

add_subdirectory(glfw-3.0.1)
