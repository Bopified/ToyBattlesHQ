cmake_minimum_required(VERSION 3.26)
project(Microvolts-Emulator-V2 LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(VCPKG_ROOT "${CMAKE_SOURCE_DIR}/ExternalLibraries/vcpkg")
set(VCPKG_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

if(NOT EXISTS "${VCPKG_TOOLCHAIN_FILE}")
    message(STATUS "vcpkg not found, cloning into ExternalLibraries/vcpkg...")
    execute_process(
        COMMAND git clone https://github.com/microsoft/vcpkg.git "${VCPKG_ROOT}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone vcpkg")
    endif()

    message(STATUS "Bootstrapping vcpkg...")
    if(WIN32)
        execute_process(COMMAND "${VCPKG_ROOT}/bootstrap-vcpkg.bat")
    else()
        execute_process(COMMAND "${VCPKG_ROOT}/bootstrap-vcpkg.sh")
    endif()
endif()

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_TOOLCHAIN_FILE}" CACHE STRING "vcpkg toolchain" FORCE)

if(DEFINED ENV{VCPKG_TRIPLET})
    set(VCPKG_TRIPLET $ENV{VCPKG_TRIPLET} CACHE STRING "Override vcpkg triplet")
elseif(MSVC)
    set(VCPKG_TRIPLET "x64-windows")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND WIN32)
    set(VCPKG_TRIPLET "x64-mingw-dynamic")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND WIN32)
    set(VCPKG_TRIPLET "x64-mingw-dynamic")
elseif(APPLE)
    if(CMAKE_OSX_ARCHITECTURES MATCHES "arm64")
        set(VCPKG_TRIPLET "arm64-osx")
    else()
        set(VCPKG_TRIPLET "x64-osx")
    endif()
elseif(UNIX)
    set(VCPKG_TRIPLET "x64-linux")
endif()


if(EXISTS "${CMAKE_SOURCE_DIR}/vcpkg.json")
    message(STATUS "Installing vcpkg packages for triplet ${VCPKG_TRIPLET}...")
    execute_process(
        COMMAND "${VCPKG_ROOT}/vcpkg" install --triplet ${VCPKG_TRIPLET}
        RESULT_VARIABLE VCPKG_RES
        OUTPUT_VARIABLE VCPKG_OUT
        ERROR_VARIABLE VCPKG_ERR
    )
    if(NOT VCPKG_RES EQUAL 0)
        message(FATAL_ERROR "vcpkg failed to install packages:\n${VCPKG_OUT}\n${VCPKG_ERR}")
    endif()
endif()


if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_WIN32_WINNT=0x0601 /bigobj")
    add_compile_options(/W0 /wd4996)
elseif(UNIX)
    add_compile_options(-w)
endif()


include_directories(PUBLIC ${CMAKE_SOURCE_DIR}/ExternalLibraries)

add_subdirectory(Common)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Common/include)

add_subdirectory(AuthServer)
add_subdirectory(CastServer)
add_subdirectory(MainServer)
