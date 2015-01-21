cmake_minimum_required(VERSION 2.8.4)
project(NN_Reactions)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_library(LFISSION Fission DOC "LLNL Fission Library")
if(NOT LFISSION)
    message(FATAL_ERROR "Could not find LLNL Fission Library libFission")
endif()
include_directories(BEFORE /usr/local/include/freya)

set(SOURCE_FILES main.cpp)
add_executable(NN_Reactions ${SOURCE_FILES})
target_link_libraries(NN_Reactions ${LFISSION})

file(INSTALL "${CMAKE_CURRENT_SOURCE_DIR}/plot.gnu" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(INSTALL "${CMAKE_CURRENT_SOURCE_DIR}/make_plots.sh" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

