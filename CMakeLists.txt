cmake_minimum_required(VERSION 3.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(libnv-asset-manager)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME main-test COMMAND nv_page_size_test)
add_test(NAME asset-test COMMAND nv_asset_test)
add_test(NAME texture-test COMMAND nv_texture_test)
