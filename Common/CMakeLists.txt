cmake_minimum_required(VERSION 3.26)
project(Common LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(asio CONFIG REQUIRED)
find_package(cryptopp CONFIG REQUIRED)
find_package(unofficial-mariadb-connector-cpp CONFIG REQUIRED)

file(GLOB_RECURSE LIBRARY_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
add_library(Common STATIC Common.cpp ${LIBRARY_SOURCES})

target_include_directories(Common
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_SOURCE_DIR}/ExternalLibraries
        ${CMAKE_SOURCE_DIR}/Common/include/Utils
)

target_link_libraries(Common
    PRIVATE
        asio::asio
        cryptopp::cryptopp
        unofficial::mariadb-connector-cpp::mariadbcpp
)

if(WIN32)
    target_link_libraries(Common PRIVATE wsock32 ws2_32)
endif()

set_target_properties(Common PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/ExternalLibraries/CommonLib
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/ExternalLibraries/CommonLib
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/ExternalLibraries/CommonLib
    ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}/ExternalLibraries/CommonLib
    ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_SOURCE_DIR}/ExternalLibraries/CommonLib
)
