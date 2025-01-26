cmake_minimum_required(VERSION 3.30)

project(BlackMagicDecklinkAPIExample LANGUAGES CXX)

# Add the include directory for headers
include_directories(${CMAKE_SOURCE_DIR}/api_includes)

# Add the executable target
add_executable(decklinkInfo main.cpp)