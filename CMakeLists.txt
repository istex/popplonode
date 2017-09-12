cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 14)
# Name of the project (will be the name of the plugin)
project(popplonode)

# Build poppler like an external project
include(ExternalProject)
ExternalProject_Add(
  poppler
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/lib/poppler
  PREFIX ${CMAKE_SOURCE_DIR}/lib/poppler
  CONFIGURE_COMMAND ${CMAKE_SOURCE_DIR}/lib/poppler/configure --prefix=${CMAKE_SOURCE_DIR}/lib/poppler --enable-build-type=release --enable-libopenjpeg=none --disable-libnss --disable-libtiff --disable-libpng --disable-splash-output --disable-cairo-output --disable-poppler-glib --disable-poppler-qt4 --disable-poppler-qt5 --disable-gtk-test --disable-utils --enable-cms=none --enable-dctdecoder=none --disable-zlib
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
)

# Build a shared library named after the project from the files in project
file(GLOB SOURCE_FILES "*.cpp" "*.h")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
include_directories(${CMAKE_JS_INC})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules/find-modules")
ExternalProject_Get_Property(poppler install_dir)
include_directories(${install_dir})
# Gives our library file a .node extension without any "lib" prefix
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

# Essential include files to build a node addon,
# You should add this line in every CMake.js based project
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC})

add_dependencies(popplonode poppler)
# Essential library files to link to a node addon
# You should add this line in every CMake.js based project
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})
target_link_libraries(${PROJECT_NAME} ${install_dir}/lib/libpoppler-cpp.so)