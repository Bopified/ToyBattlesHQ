cmake_minimum_required(VERSION 3.26)
project(MainServer LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB_RECURSE MAIN_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
add_executable(MainServer ${MAIN_SOURCES})

find_package(unofficial-mariadb-connector-cpp CONFIG REQUIRED)
find_package(asio CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS json)
find_package(OpenSSL REQUIRED)
find_package(CryptoPP REQUIRED)
find_package(range-v3 REQUIRED)

set(Boost_NO_BOOST_CMAKE ON)
set(Boost_NO_WARN_NEW_VERSIONS ON)

target_include_directories(MainServer
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_SOURCE_DIR}/Common/include
        ${CMAKE_SOURCE_DIR}/ExternalLibraries
        ${CMAKE_SOURCE_DIR}/ExternalLibraries/DirectXMath/Inc
        ${CMAKE_SOURCE_DIR}/Common/include/Utils
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(MainServer
    PRIVATE
        Common
        asio::asio
        unofficial::mariadb-connector-cpp::mariadbcpp
        OpenSSL::SSL
        OpenSSL::Crypto
        cryptopp::cryptopp
        range-v3::range-v3
        ${Boost_LIBRARIES}
)

if(WIN32)
    target_link_libraries(MainServer PRIVATE wsock32 ws2_32)
endif()

if(MSVC)
    add_compile_options(/W0)
else()
    add_compile_options(-w)
endif()

set_target_properties(MainServer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
