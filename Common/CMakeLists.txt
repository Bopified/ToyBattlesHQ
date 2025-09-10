project(Common LANGUAGES CXX)

file(GLOB_RECURSE COMMON_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
)

add_library(Common STATIC
    Common.cpp
    ${COMMON_SOURCES}
)

target_include_directories(Common
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_SOURCE_DIR}/ExternalLibraries
        ${CMAKE_SOURCE_DIR}/Common/include/Utils
)


target_link_libraries(Common
    PRIVATE   
        cryptopp::cryptopp
        unofficial::mariadb-connector-cpp::mariadbcpp
)

if (WIN32)
    target_link_libraries(Common PRIVATE wsock32 ws2_32)
endif()

