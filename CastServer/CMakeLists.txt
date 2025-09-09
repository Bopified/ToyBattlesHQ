cmake_minimum_required(VERSION 3.26)
project(CastServer LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB_RECURSE CAST_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
add_executable(CastServer ${CAST_SOURCES})

find_package(asio CONFIG REQUIRED)
find_package(Boost 1.85.0 REQUIRED COMPONENTS system)

target_include_directories(CastServer
    PUBLIC
        ${CMAKE_SOURCE_DIR}/Common/include
        ${CMAKE_SOURCE_DIR}/ExternalLibraries
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_SOURCE_DIR}/ExternalLibraries/DirectXMath/Inc
        ${CMAKE_SOURCE_DIR}/Common/include/Utils
)

target_link_libraries(CastServer
    PRIVATE
        Common
        asio::asio
        Boost::system
)

if(WIN32)
    target_link_libraries(CastServer PRIVATE wsock32 ws2_32)
endif()

add_dependencies(CastServer Common)

set_target_properties(CastServer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
