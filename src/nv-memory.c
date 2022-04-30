#include "nv-memory.h"
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

#define OFFSET_SIZE sizeof(uint16_t)

#ifndef align_up
#define align_up(num, align) \
    (((num) + ((align) - 1)) & ~((align) - 1))
#endif

static inline uint32_t get_page_size() {
  return sysconf(_SC_PAGESIZE);
}

nv_memory_status_t nv_malloc(size_t size, nv_memory_block_t * block) {
  if(size == 0)
    return bad_allocation;

  block->position = memalign(get_page_size(), size);
  return ok;
}

void nv_free(nv_memory_block_t * block) {
  if(block->size != 0) {
    free(block->position);
    block->size = 0;
  }
}

#undef OFFSET_SIZE
#undef align_up
