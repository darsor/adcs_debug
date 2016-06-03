cmake_minimum_required (VERSION 3.0.2 FATAL_ERROR)
project (COSMOS_Server CXX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -o3 -Wall")

set (COMMON_LIBS ${EXTRA_LIBS} wiringPi)

set(COMMON_SOURCES
    cosmos/cosmos.cpp
    cosmos/packets.cpp
    cosmos/cosmosQueue.cpp
    adcs.cpp
    main.cpp
)

add_executable (adcs ${COMMON_SOURCES})
target_link_libraries (adcs ${COMMON_LIBS})
