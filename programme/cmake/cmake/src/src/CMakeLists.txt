set(LIB_LIST hello.so)
set(SRC_LIST main.c)
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output/bin)
add_executable(hello ${SRC_LIST})
target_link_libraries(hello ${LIB_LIST})
