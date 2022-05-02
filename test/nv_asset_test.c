#include <nv-asset-manager.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
int main() {
  nv_memory_block_t block;
  assert(nv_malloc(100, &block) == ok);

  nv_asset_map_t * map = nv_init_asset_map(&block);

  char * hello = "Hello ";
  uint32_t hello_id = nv_asset_manager_push(&block, map, hello, strlen(hello));
  char * world = "World";
  uint32_t world_id = nv_asset_manager_push(&block, map, world, strlen(world));

  nv_asset_block_t buf; 
  nv_asset_manager_get(&block, map, hello_id, &buf);
  assert(strncmp(buf.data, hello, buf.size) == 0);

  nv_asset_manager_get(&block, map, world_id, &buf);
  assert(strncmp(buf.data, world, buf.size) == 0);

  nv_asset_manager_pop(&block, map);
  int32_t hello_size = (int32_t) strlen(hello);
  int32_t size_t_size = (int32_t) sizeof(uint32_t);
  assert(block.remaining == (int32_t)(100 - hello_size - size_t_size));
  nv_asset_manager_pop(&block, map);
  assert(block.remaining == 100);
  assert(block.top == 0);

  nv_free_asset_map(map);
  nv_free(&block);
}
