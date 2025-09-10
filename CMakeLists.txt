cmake_minimum_required(VERSION 3.26)
project(Microvolts-Emulator-V2 LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0x0601 -Wa,-mbig-obj")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--allow-multiple-definition")
else()
    set(CMAKE_EXECUTABLE_SUFFIX ".elf")
    set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -Wl,--allow-multiple-definition -Wl,-rpath=. -Wl,-rpath=/data/data/com.termux/files/usr/lib -Wl,--enable-new-dtags"
    )
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output)

find_package(Boost 1.73.0 REQUIRED COMPONENTS system json beast asio)
find_package(OpenSSL REQUIRED)
find_package(cryptopp CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_package(unofficial-mariadb-connector-cpp CONFIG REQUIRED)

include_directories(PUBLIC ${CMAKE_SOURCE_DIR}/ExternalLibraries)
add_subdirectory(Common)
add_subdirectory(AuthServer)
add_subdirectory(CastServer)
add_subdirectory(MainServer)

