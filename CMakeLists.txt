cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_BUILD_TYPE Debug)

project(Evolution)

set(CMAKE_CXX_FLAGS "-std=c++0x -g")
set(TARGET ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH})

option(DEBUG_MODE "DEBUG MODE." OFF)
option(LOG "LOG MODE." OFF)
option(UNIT_TEST "UNIT TEST." OFF)

message("")
message("-- DEBUG MODE ${DEBUG_MODE}")
message("-- UNIT_TEST ${UNIT_TEST}")
message("")


find_package(SFML 2
  COMPONENTS 
    system window graphics network audio REQUIRED)

if(UNIT_TEST)
    add_subdirectory(unit-test)
endif(UNIT_TEST)

if(DEBUG_MODE)
add_definitions(-DDEBUG_MODE)
endif(DEBUG_MODE)

set(LIBS pthread sfml-graphics sfml-audio sfml-window sfml-system)

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/config/
    ${CMAKE_SOURCE_DIR}/resource/json/include/
	${CMAKE_SOURCE_DIR}/src/Common/inc/
    ${CMAKE_SOURCE_DIR}/src/Food/api/
    ${CMAKE_SOURCE_DIR}/src/Food/inc/
    ${CMAKE_SOURCE_DIR}/src/Organism/api/
    ${CMAKE_SOURCE_DIR}/src/Organism/inc
    ${CMAKE_SOURCE_DIR}/src/Manager/api/
    ${CMAKE_SOURCE_DIR}/src/Manager/inc
    ${CMAKE_SOURCE_DIR}/src/Behaviour/api/
    ${CMAKE_SOURCE_DIR}/src/Behaviour/inc
    ${CMAKE_SOURCE_DIR}/src/PointOfInterest/api/
    ${CMAKE_SOURCE_DIR}/src/PointOfInterest/inc
)

link_directories(
)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCE_FILES
	Evolution.cpp /
    src/*.cpp
)	

add_executable(${TARGET} ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(${TARGET} ${LIBS})