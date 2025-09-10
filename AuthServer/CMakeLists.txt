project(AuthServer LANGUAGES CXX)

add_executable(AuthServer
    AuthServerMain.cpp
    src/AuthServer.cpp
    src/AuthSession.cpp
    src/DbPlayerInfo.cpp
)


target_include_directories(AuthServer PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)


target_link_libraries(AuthServer PRIVATE
        Common
        unofficial::mariadb-connector-cpp::mariadbcpp
)

if (WIN32)
    target_link_libraries(AuthServer PRIVATE wsock32 ws2_32)
endif()


set_target_properties(AuthServer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

