project(NFrame)

file(GLOB_RECURSE NFRAME_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

message(STATUS "NFRAME_SOURCES:")
foreach(src ${NFRAME_SOURCES})
    message(STATUS "  ${src}")
endforeach()


set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/GLFW)



if(NF_BUILD_DLL)
    add_library(NFrame SHARED ${NFRAME_SOURCES})
    add_custom_command(TARGET NFrame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying DLL..."
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/libNFrame.dll"
            "${CMAKE_BINARY_DIR}/SandBox/libNFrame.dll"
    )
else()
    add_library(NFrame STATIC ${NFRAME_SOURCES})
endif()


target_include_directories(NFrame PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    vendor/spdlog/include
    vendor/GLFW/include
)

target_link_libraries(NFrame PUBLIC glfw opengl32)
target_precompile_headers(NFrame PRIVATE "include/NFrame/nfpch.h")
target_compile_definitions(NFrame PUBLIC NF_PLATFORM_WINDOWS)

if(NF_BUILD_DLL)
    target_compile_definitions(NFrame PUBLIC NF_BUILD_DLL)
endif()


get_target_property(NFRAME_LINK_LIBS NFrame LINK_LIBRARIES)
message(STATUS "🔗 NFrame is linking with libraries:")
foreach(lib ${NFRAME_LINK_LIBS})
    message(STATUS "  - ${lib}")
endforeach()