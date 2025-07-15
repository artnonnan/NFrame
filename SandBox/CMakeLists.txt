project(SandBox)

add_executable(SandBoxApp
    src/SandBoxMain.cpp
)

# Link กับ NFrame
target_link_libraries(SandBoxApp PRIVATE NFrame)

# รวม include path จาก NFrame
#target_include_directories(SandBoxApp PRIVATE
#    ${CMAKE_SOURCE_DIR}/include
#)
