cmake_minimum_required(VERSION 2.8.0)

project(pseudoform)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-extras/")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package(SFML REQUIRED)
find_package(OGRE REQUIRED)
find_package(Bullet REQUIRED)
find_package(MyGUI REQUIRED)
find_package(MyGUI_PLATFORM REQUIRED)
find_package(Boost COMPONENTS filesystem system python date_time REQUIRED)

add_definitions(-Wall)
set(CMAKE_BUILD_TYPE "Debug")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(
	"${CMAKE_SOURCE_DIR}/include/"
	${Boost_INCLUDE_DIRS}
	${SFML_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
        ${MYGUI_INCLUDE_DIR}
        ${MYGUI_PLATFORM_INCLUDE_DIR}
	${BULLET_INCLUDE_DIRS}
)

add_subdirectory("${CMAKE_SOURCE_DIR}/src/")
add_subdirectory("${CMAKE_SOURCE_DIR}/samples/")