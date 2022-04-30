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
  void * position;
  uint32_t size;
} nv_memory_block_t;

nv_memory_status_t nv_malloc(size_t size, nv_memory_block_t * block);
void nv_free(nv_memory_block_t * block);

#endif
