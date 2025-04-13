cmake_minimum_required(VERSION 3.14)
project(FalloutPickle)

# JSON include
include_directories(${CMAKE_SOURCE_DIR}/extern/json/single_include)

# Declare F4SE path as a cache variable (ensures CMake propagates it)
set(F4SE_PATH "C:/SDKs/F4SE" CACHE PATH "Path to F4SE dev kit")

# Local includes
include_directories(src)
include_directories(${CMAKE_SOURCE_DIR}/src/f4se_shims)

set(CMAKE_CXX_STANDARD 17)

# Source files
file(GLOB SOURCES src/*.cpp)

# Build shared library (DLL)
add_library(FalloutPickle SHARED ${SOURCES}
  src/f4se_shims/CommandTable.cpp
)
target_include_directories(FalloutPickle PRIVATE
    ${F4SE_PATH}/f4se
    ${F4SE_PATH}/f4se_common
)

# Link against F4SE
target_link_libraries(FalloutPickle
    ${F4SE_PATH}/f4se/f4se_common.lib
    ${F4SE_PATH}/f4se/f4se.lib
)

# Output DLL to build folder
set_target_properties(FalloutPickle PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build"
)
