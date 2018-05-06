cmake_minimum_required( VERSION 2.8.9 )
project( Proj LANGUAGES CXX )

# Compiler stuff

set( CMAKE_C_COMPILER /usr/bin/clang )
set( CMAKE_CXX_COMPILER /usr/bin/clang++ )

set( CMAKE_CXX_STANDARD 17 )
#set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O1" )
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3" )

# Adding include directory for audio

include_directories( "ext/fmod/4.3" )

# Linking libraries

link_directories( "ext/jpeg/" "ext/fmod/4.3/" "obj/" )
link_libraries( "GL" "GLU" "glut" "libjpeg.a" "m" "libfmodex64.so" )

# Adding sources

# Pre-compiled objects
set( OBJS "obj/OpenGL64.o" )
set_source_files_properties( ${OBJS} PROPERTIES
  EXTERNAL_OBJECT true
  GENERATED true
)

# Building object files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Final executable
add_executable(cstrike64 ${OBJS} ${SOURCES})
