cmake_minimum_required(VERSION 3.6)
project(SoccerRL)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )
find_package( Boost 1.63.0 REQUIRED COMPONENTS system )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${Boost_INCLUDE_DIRS} )

set(SOURCE_FILES
    Tracker/src/Constants.hpp
    Tracker/src/Functions.hpp
    Tracker/src/Functions.cpp
    Tracker/src/BallTracker.hpp
    Tracker/src/BallTracker.cpp
    Tracker/src/MarkerFinder.hpp
    Tracker/src/MarkerFinder.cpp
    Tracker/src/RobotTracker.hpp
    Tracker/src/RobotTracker.cpp
    Tracker/src/main.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Tracker/bin)

add_executable(SoccerRL ${SOURCE_FILES})
target_link_libraries( SoccerRL ${OpenCV_LIBS} )
target_link_libraries( SoccerRL ${Boost_LIBRARIES} )