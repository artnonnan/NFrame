project(SandBox)

file(GLOB SANDBOX_SRC CONFIGURE_DEPENDS "src/*.cpp")

add_executable(SandBoxApp ${SANDBOX_SRC})

target_link_libraries(SandBoxApp PRIVATE NFrame)