cmake_minimum_required(VERSION 3.3)
project(Atomas)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_BUILD_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")


set(SOURCE_FILES main.cpp Atom.h AtomRing.h AtomDisplay.h MenuScreen.h GameScreen.h Screen.h)
add_executable(Atomas ${SOURCE_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/SFML-2.3.2/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Atomas ${SFML_LIBRARIES})
endif()