include_directories(../src)
add_executable(nv_page_size_test nv_block_test.c)
target_link_libraries(nv_page_size_test PUBLIC nv-asset-manager)

add_executable(nv_asset_test nv_asset_test.c)
target_link_libraries(nv_asset_test PUBLIC nv-asset-manager)

set(RESOURCE_FILES test_rgba.png)
add_executable(nv_texture_test
  nv_texture_test.c
  ${RESOURCE_FILES})
target_link_libraries(nv_texture_test PUBLIC nv-asset-manager)
set_target_properties(nv_texture_test PROPERTIES RESOURCE "${RESOURCE_FILES}")
