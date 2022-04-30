include_directories(../src)
add_executable(nv_page_size_test nv_page_size_test.c)
target_link_libraries(nv_page_size_test nv-memory)
