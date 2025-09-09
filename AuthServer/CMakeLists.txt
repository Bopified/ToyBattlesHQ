cmake_minimum_required(VERSION 3.26)
project(AuthServer LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


find_package(unofficial-mariadb-connector-cpp CONFIG REQUIRED)
find_package(asio CONFIG REQUIRED)


add_executable(AuthServer
    AuthServerMain.cpp
    src/AuthServer.cpp
    src/AuthSession.cpp
    src/DbPlayerInfo.cpp
)

target_include_directories(AuthServer
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_SOURCE_DIR}/Common/include
        ${CMAKE_SOURCE_DIR}/Common/include/Utils
        ${CMAKE_SOURCE_DIR}/ExternalLibraries
)


target_link_libraries(AuthServer
    PRIVATE
        Common
        asio::asio
        unofficial::mariadb-connector-cpp::mariadbcpp
)

if(WIN32)
    target_link_libraries(AuthServer PRIVATE wsock32 ws2_32)
endif()


add_dependencies(AuthServer Common)
set_target_properties(AuthServer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
