#include <nv-image-asset.h>
#include <nv-asset-manager.h>

int main() {
  nv_memory_block_t block;
  assert(nv_malloc(10*4096, &block) == 0);
  nv_asset_map_t *map = nv_init_asset_map(&block);
  nv_texture_info_t tex = load_texture("./res/test_rgba.png", &block, map);
  printf("%d\n", tex.x);
  nv_free_asset_map(map);
  nv_free(&block);
}
