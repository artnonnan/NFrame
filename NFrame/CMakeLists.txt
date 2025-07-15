project(NFrame)

# สร้าง Static Library
file(GLOB_RECURSE NFRAME_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(NFrame STATIC ${NFRAME_SOURCES})

target_include_directories(NFrame PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    vendor/spdlog/include
)

# Optional: ถ้า NFrame มี main() ก็สร้าง executable แยกให้รัน
#add_executable(NFrameApp
#    src/NFrameMain.cpp
#)
#target_link_libraries(NFrameApp PRIVATE NFrame)
