cmake_minimum_required(VERSION 3.0)

project(Naavimac)

add_definitions(-std=c++11)


set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
#set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} lib/glimac/include lib/third-party/include app/include)

set(ALL_LIBRARIES glimac ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

add_subdirectory(lib/glimac)
add_subdirectory(app)
add_subdirectory(doc)

file(COPY assets DESTINATION bin/${CMAKE_BUILD_TYPE})