cmake_minimum_required(VERSION 3.6)
project(SimulatedRL)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )
find_package( Boost 1.63.0 REQUIRED COMPONENTS system )
include_directories( include ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} )

set(HEADER_FILES
    include/Constants.hpp
    include/Functions.hpp
    include/ActionValueFunction.hpp
    include/SarsaParams.hpp
    include/Tiles.hpp
    include/TrueOnlineSarsaUpdate.hpp
)

set(SOURCE_FILES
    src/Simulator.cpp
    src/Functions.cpp
    src/Tiles.cpp
    src/TrueOnlineSarsaUpdate.cpp
    src/main.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(SimulatedRL ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries( SimulatedRL ${OpenCV_LIBS} )
target_link_libraries( SimulatedRL ${Boost_LIBRARIES} )