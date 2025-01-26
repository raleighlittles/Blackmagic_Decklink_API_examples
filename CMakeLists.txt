cmake_minimum_required(VERSION 3.30)

project(BlackMagicDecklinkAPIExample LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        set(BUILD_FOR_WIN TRUE)
        message("Windows platform detected..")
else()
        message("Linux platform detected..")
endif()

option(STATIC_BUILD "Build a static binary." ${BUILD_FOR_WIN})

if (STATIC_BUILD)
        set(CMAKE_EXE_LINKER_FLAGS "-static")
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" CONFIG)
        set(BUILD_SHARED_LIBS OFF)
endif()

if (BUILD_FOR_WIN)
    message("Building for Windows..")
    set(CMAKE_SYSTEM_NAME Windows)
    set(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
    set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
    set(CMAKE_RC_COMPILER i686-w64-mingw32-windres)
    set(CMAKE_RANLIB i686-w64-mingw32-ranlib)
    include_directories(${CMAKE_SOURCE_DIR}/win_includes)
else()
    message("Building for Linux..")
    # Add the include directory for headers
    include_directories(${CMAKE_SOURCE_DIR}/linux_includes)
endif()

# Add the executable target
add_executable(decklinkInfo main.cpp)