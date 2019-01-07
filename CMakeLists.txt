# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (ProducerConsumer)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/InputBuffer.cpp
    src/OutputBuffer.cpp
    src/main.cpp
)

#Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -O0 -std=gnu++0x -pthread")

# Add an executable with the above sources
add_executable(ProducerConsumer ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(ProducerConsumer
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)
