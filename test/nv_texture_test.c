#include <assert.h>
#include <nv-image-asset.h>
#include <nv-asset-manager.h>

int main() {
  nv_memory_block_t block;
  assert(nv_malloc(200*4096, &block) == 0);
  nv_asset_map_t *map = nv_init_asset_map(&block);
  nv_texture_info_t tex = load_texture("test/test_rgba.png", &block, map);
  assert(tex.x == 250);
  assert(tex.y == 200);
  assert(tex.depth == 4);
  assert(tex.id == 0);
  nv_asset_block_t ret;
  nv_asset_manager_get(&block, map, tex.id, &ret);
  nv_free_asset_map(map);
  nv_free(&block);
}
