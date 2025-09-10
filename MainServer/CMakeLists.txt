project(MainServer LANGUAGES CXX)

file(GLOB_RECURSE MAIN_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
)

add_compile_options(-Wbuiltin-macro-redefined)


add_executable(MainServer
    ${MAIN_SOURCES}
)

target_include_directories(MainServer
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
)

find_path(JWT_CPP_INCLUDE_DIRS "jwt-cpp/base.h")
target_include_directories(MainServer PRIVATE ${JWT_CPP_INCLUDE_DIRS})

target_link_libraries(MainServer
    PRIVATE
        Common
        unofficial::mariadb-connector-cpp::mariadbcpp
        OpenSSL::SSL
        OpenSSL::Crypto
        cryptopp::cryptopp
        range-v3::range-v3
        Boost::json
)

if (WIN32)
    target_link_libraries(MainServer PRIVATE wsock32 ws2_32)
endif()

if (MSVC)
    target_compile_options(MainServer PRIVATE /W0)
else()
    target_compile_options(MainServer PRIVATE -w)
endif()

set_target_properties(MainServer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

