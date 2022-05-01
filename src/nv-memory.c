#include "nv-memory.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#endif

#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L
#define MEMALIGN(ptr, align, size) posix_memalign(ptr, align, size)
#elif _WIN32
// Source: https://stackoverflow.com/a/33696858
#define MEMALIGN(p, a, s) (((*(p)) = _aligned_malloc((s), (a))), *(p) ?0 :errno)
#else
#error "ERROR: aligned malloc is not supported."
#endif

static inline uint32_t get_page_size() {
#ifdef _WIN32
  SYSTEM_INFO sysinfo;
  GetSystemInfo(&sysinfo);
  return (uint32_t) sysinfo.dwAllocationGranularity;
#else
  return sysconf(_SC_PAGESIZE);
#endif
}

void nv_init_asset_map(nv_memory_block_t * block, nv_asset_map_t * map) {
  map->block = block;
  map->count = 0;
}

#include <stdio.h>
int32_t nv_asset_manager_push(nv_memory_block_t * block,
    nv_asset_map_t * map, const char * data, size_t data_len) {
  if(data_len+sizeof(size_t) > block->remaining) return -1;
  if(map->block != block) return -1;
  
  map->count++;
  map->map = reallocarray(map->map, map->count, sizeof(uint32_t));
  map->map[map->count-1] = block->top;
  
  memcpy(block->data+block->top, &data_len, sizeof(size_t));
  block->top+=sizeof(size_t);
  strncpy(block->data+block->top, data, data_len);
  block->top+=data_len;
  block->remaining -= (data_len+sizeof(size_t));
  printf("%d\n", block->remaining);
  return map->count-1;
}

void nv_asset_manager_get(nv_memory_block_t * block, nv_asset_map_t * map, uint32_t asset_id, nv_asset_block_t * ret) {
  if(map->block != block) return;
  
  uint32_t top = *(map->map+asset_id);
  size_t size = *(block->data+top);
  top+=sizeof(size_t);
  ret->data = block->data+top;
  ret->size = size;
}

int32_t nv_asset_manager_pop(nv_memory_block_t * block, nv_asset_map_t * map) {
  if(map->block != block) return -1;
  map->count--;
  uint32_t top = *(map->map+map->count);
  size_t data_ret_len = *(block->data+top);
  if(map->count>0) {
    map->map = reallocarray(map->map, map->count, sizeof(uint32_t));
  }
  block->top = map->map[map->count];
  block->remaining += (data_ret_len+sizeof(size_t));
  return 0;
}

nv_memory_status_t nv_malloc(size_t size, nv_memory_block_t * block) {
  if(size == 0)
    return bad_allocation;

  if(MEMALIGN((void*)&block->data, get_page_size(), size))
    return bad_allocation;

  block->size = size;
  block->remaining = size;
  block->top = 0;
  return ok;
}

void nv_free(nv_memory_block_t * block) {
  if(block->size != 0) {
    free(block->data);
    block->size = 0;
    block->remaining = 0;
    block->top = 0;
  }
}
#undef MEMALIGN
