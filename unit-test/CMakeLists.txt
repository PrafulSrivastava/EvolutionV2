cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_BUILD_TYPE Debug)

project(EvolutionTest)

set(CMAKE_CXX_FLAGS "-std=c++0x -g -pthread")
set(TARGET ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH})

add_definitions(-DUNIT_TEST)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


find_package(SFML 2
  COMPONENTS 
    system window graphics network audio REQUIRED)

set(LIBS 
pthread 
gtest
gtest_main 
sfml-graphics 
sfml-audio 
sfml-window 
sfml-system)

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/config/
	${CMAKE_SOURCE_DIR}/src/Common/
    ${CMAKE_SOURCE_DIR}/src/Food/api/
    ${CMAKE_SOURCE_DIR}/src/Food/inc/
    ${CMAKE_SOURCE_DIR}/src/Organism/api/
    ${CMAKE_SOURCE_DIR}/src/Organism/inc
)

link_directories(
)


file(GLOB_RECURSE ${PROJECT_NAME}_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp /
    ${CMAKE_SOURCE_DIR}/unit-test/*.cpp
)	

add_executable(${TARGET} ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(${TARGET} ${LIBS})