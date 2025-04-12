cmake_minimum_required(VERSION 3.14)
project(FalloutPickle)
include_directories(${CMAKE_SOURCE_DIR}/extern/json/include)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    src
    ${F4SE_PATH}/f4se
)

file(GLOB SOURCES src/*.cpp)

add_library(FalloutPickle SHARED ${SOURCES})

target_link_libraries(FalloutPickle
    ${F4SE_PATH}/f4se/f4se_common.lib
    ${F4SE_PATH}/f4se/f4se.lib
)

set_target_properties(FalloutPickle PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
)
