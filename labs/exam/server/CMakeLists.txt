project(lab01_single_thread_server)

include_directories(include)
file(GLOB SRC src/*.cpp src/*.cxx)
add_executable(${PROJECT_NAME} ${SRC} ../../lab05/include/net_common.h ../../lab05/include/ping_hlp.h)

target_link_libraries(${PROJECT_NAME} ${COMMON_DEPENDENCIES})
