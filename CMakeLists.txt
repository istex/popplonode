cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)
# Name of the project (will be the name of the plugin)
project(popplonode)
# Build a shared library named after the project from the files in project
file(GLOB SOURCE_FILES "*.cpp" "*.h")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
include_directories(${CMAKE_JS_INC})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/extra-cmake-modules/find-modules")
find_package(Poppler REQUIRED)
include_directories(${Poppler_INCLUDE_DIRS})

# Gives our library file a .node extension without any "lib" prefix
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

# Essential include files to build a node addon,
# You should add this line in every CMake.js based project
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC})

# Essential library files to link to a node addon
# You should add this line in every CMake.js based project
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})
target_link_libraries(${PROJECT_NAME} ${Poppler_LIBRARIES})