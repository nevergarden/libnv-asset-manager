include_directories(../src)
add_executable(nv_page_size_test nv_block_test.c)
target_link_libraries(nv_page_size_test nv-memory)

add_executable(nv_asset_test nv_asset_test.c)
target_link_libraries(nv_asset_test nv-memory)
