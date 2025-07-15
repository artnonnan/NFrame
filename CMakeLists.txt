cmake_minimum_required(VERSION 3.15)
project(NFrame)

# ใช้ C++20+
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Option: Build as DLL or static
option(NF_BUILD_DLL "Build NFrame as DLL" ON)



# ตัวเลือกว่าจะ build อะไร
option(BUILD_NFRAME "Build NFrame only" ON)
option(BUILD_SANDBOX "Build SandBox App" ON)

# เพิ่ม subdirectory ตาม options
if(BUILD_NFRAME)
    add_subdirectory(NFrame)
endif()

if(BUILD_SANDBOX)
    add_subdirectory(SandBox)
endif()
