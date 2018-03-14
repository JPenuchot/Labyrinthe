cmake_minimum_required( VERSION 2.8.9 )
project( Proj LANGUAGES CXX )

# Compiler stuff

set( CMAKE_C_COMPILER /usr/bin/clang )
set( CMAKE_CXX_COMPILER /usr/bin/clang++ )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3" )
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -mavx2 -mfma" )

# Adding include directory for audio

include_directories( "ext/fmod/4.3" )

# Linking libraries

link_directories( "ext/jpeg/" )
link_libraries( "GL" "GLU" "glut" "jpeg" "m" )

# Adding sources

# Pre-compiled objects
set( OBJS "obj/OpenGL64.o" "ext/fmod/4.3/libfmodex64.so" )
set_source_files_properties( ${OBJS} PROPERTIES
  EXTERNAL_OBJECT true
  GENERATED true
)

# Building object files
add_library( Labyrinthe OBJECT "src/Labyrinthe.cpp" )
add_library( Chasseur   OBJECT "src/Chasseur.cpp" )

# Final executable
add_executable( prog
  ${OBJS}
  $<TARGET_OBJECTS:Labyrinthe>
  $<TARGET_OBJECTS:Chasseur>
)
