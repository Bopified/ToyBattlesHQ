project(CastServer LANGUAGES CXX)


file(GLOB_RECURSE CAST_SOURCES CONFIGURE_DEPENDS 
	${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
)

add_executable(CastServer
    ${CAST_SOURCES}
)


target_include_directories(CastServer PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
)

find_package(directxmath CONFIG REQUIRED)

target_link_libraries(CastServer
    PRIVATE
        Common
        Boost::system
)


if (WIN32)
    target_link_libraries(CastServer PRIVATE wsock32 ws2_32)
endif()

# Output binary at repo root
set_target_properties(CastServer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

