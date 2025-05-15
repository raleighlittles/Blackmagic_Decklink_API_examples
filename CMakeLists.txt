cmake_minimum_required(VERSION 3.30)

project(BlackMagicDeckLinkAPIExample LANGUAGES CXX
        DESCRIPTION "API examples for interfacing with a BlackMagic DeckLink capture card"
        HOMEPAGE_URL "https://github.com/raleighlittles/Blackmagic_Decklink_API_examples")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(COMPILE_WARNING_AS_ERROR ON)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        set(BUILD_FOR_WIN TRUE)
        message("Windows platform detected..")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        message("Linux platform detected..")
else()
        message("Unsupported platform!")
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