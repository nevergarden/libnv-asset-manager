#include "nv-image-asset.h"
#include "nv-asset-manager.h"

 nv_texture_info_t load_texture(const char * path, nv_memory_block_t * block, nv_asset_map_t * map) {
  nv_texture_info_t texture_info;
  char * data = (char*)stbi_load(path, &texture_info.x, &texture_info.y, &texture_info.depth, 0);
  texture_info.id = nv_asset_manager_push(block, map, data, texture_info.x*texture_info.y*texture_info.depth);
  stbi_image_free(data);
  return texture_info;
}
