include_directories(../src)
add_executable(nv_page_size_test nv_block_test.c)
target_link_libraries(nv_page_size_test PUBLIC nv-asset-manager)

add_executable(nv_asset_test nv_asset_test.c)
target_link_libraries(nv_asset_test PUBLIC nv-asset-manager)

add_executable(nv_texture_test nv_texture_test.c)
target_link_libraries(nv_texture_test PUBLIC nv-asset-manager)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test_rgba.png ${CMAKE_CURRENT_BINARY_DIR}/test_rgba.png COPYONLY)
install(DIRECTORY res/ DESTINATION res)
