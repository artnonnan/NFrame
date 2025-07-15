project(NFrame)

# สร้าง Static Library
file(GLOB_RECURSE NFRAME_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

message(STATUS "NFRAME_SOURCES:")
foreach(src ${NFRAME_SOURCES})
    message(STATUS "  ${src}")
endforeach()

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
)

# Define macro สำหรับ platform และ DLL export
target_compile_definitions(NFrame PUBLIC NF_PLATFORM_WINDOWS)

if(NF_BUILD_DLL)
    target_compile_definitions(NFrame PUBLIC NF_BUILD_DLL)
endif()

# Optional: ถ้า NFrame มี main() ก็สร้าง executable แยกให้รัน
#add_executable(NFrameApp
#    src/NFrameMain.cpp
#)
#target_link_libraries(NFrameApp PRIVATE NFrame)
