cmake_minimum_required(VERSION 3.3)
project(Atomas)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_BUILD_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

find_package(Boost 1.55.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})



set(SOURCE_FILES main.cpp game/AtomRing.h
        view/AtomDisplay.h controller/Controller.h controller/GameController.h view/GameView.h model/GameModel.h
        controller/MenuController.h view/MenuView.h
        game/Atomas.cpp game/Atomas.h game/AtomRing.cpp game/AtomRing.h
        view/GameOverView.h controller/GameOverController.h view/EnterIPVIew.h controller/EnterIPController.h
        view/GameMultiView.h model/GameMultiModel.h controller/GameMultiController.h
        network/Connection.cpp network/Connection.h network/Data.cpp network/Data.h)
add_executable(Atomas ${SOURCE_FILES})

target_link_libraries(Atomas ${Boost_LIBRARIES} -lpthread )

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/SFML-2.3.2/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 COMPONENTS system window graphics network audio REQUIRED)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Atomas ${SFML_LIBRARIES})
endif()