#ifndef _NV_ASSET_MANAGER_H
#define _NV_ASSET_MANAGER_H

#include <stdlib.h>
#include <stdint.h>

typedef enum nv_memory_status_t {
  bad_allocation = -1,
  ok = 0,
} nv_memory_status_t;

// allocation block data
typedef struct nv_memory_block_t {
  char * data;
  uint32_t size;
  uint32_t remaining;
  uint32_t top;
} nv_memory_block_t;

// asset map data
typedef struct nv_asset_map_t {
  nv_memory_block_t * block;
  uint32_t * map;
  uint32_t count;
} nv_asset_map_t;

// main asset returned data
typedef struct nv_asset_block_t {
  const char * data;
  size_t size;
} nv_asset_block_t;

// Allocates a new block of memory pool
nv_memory_status_t nv_malloc(size_t size, nv_memory_block_t * block);
// Frees the allocated block pool
void nv_free(nv_memory_block_t * block);

// TODO: this should not be in public API maybe? add this to the allocator
// so when we allocate it's map is already allocated.
// -------------------------
// Initializes new asset map
nv_asset_map_t * nv_init_asset_map(nv_memory_block_t * block);
// Frees the assets map
void nv_free_asset_map(nv_asset_map_t * map);

// Pushes new asset to block returning it's id
int32_t nv_asset_manager_push(nv_memory_block_t * block, nv_asset_map_t * map, const char * data, size_t data_len);
// Gets an asset by id
void nv_asset_manager_get(nv_memory_block_t * block, nv_asset_map_t * map, uint32_t asset_id, nv_asset_block_t * ret);
// Frees some of the block, allows more allocation
int32_t nv_asset_manager_pop(nv_memory_block_t * block, nv_asset_map_t * map);
 
#endif
