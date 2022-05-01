#ifndef _NV_MEMORY_H
#define _NV_MEMORY_H

#include <stdlib.h>
#include <stdint.h>

typedef enum nv_memory_status_t {
  bad_allocation = -1,
  ok = 0,
} nv_memory_status_t;

/*
 * This is a memory block max 4GB of memory allocation.
 * it's size should be page aligned.
 */
typedef struct nv_memory_block_t {
  char * data;
  uint32_t size;
  uint32_t remaining;
  uint32_t top;
} nv_memory_block_t;

typedef struct nv_asset_map_t {
  nv_memory_block_t * block;
  uint32_t * map;
  uint32_t count;
} nv_asset_map_t;

typedef struct nv_asset_block_t {
  const char * data;
  size_t size;
} nv_asset_block_t;

nv_memory_status_t nv_malloc(size_t size, nv_memory_block_t * block);
void nv_free(nv_memory_block_t * block);

// Adds a new asset to manager returns asset id
nv_asset_map_t * init_asset_map(nv_memory_block_t * block) {
  nv_asset_map_t * map = malloc(sizeof(nv_asset_map_t));
  map->block = block;
  map->count = 0;
  map->map = NULL;
  return map;
}
void free_asset_map(nv_asset_map_t * map) {
  free(map->map);
  free(map);
}

int32_t nv_asset_manager_push(nv_memory_block_t * block, nv_asset_map_t * map, const char * data, size_t data_len);

void nv_asset_manager_get(nv_memory_block_t * block, nv_asset_map_t * map, uint32_t asset_id, nv_asset_block_t * ret);

int32_t nv_asset_manager_pop(nv_memory_block_t * block, nv_asset_map_t * map);
 
#endif
