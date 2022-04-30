#include "nv-memory.h"
#include <stdlib.h>
#include <unistd.h>

static inline uint32_t get_page_size() {
  return sysconf(_SC_PAGESIZE);
}

nv_memory_status_t nv_malloc(size_t size, nv_memory_block_t * block) {
  if(size == 0)
    return bad_allocation;

  if(posix_memalign(&block->data, get_page_size(), size))
    return bad_allocation;

  block->size = size;
  return ok;
}

void nv_free(nv_memory_block_t * block) {
  if(block->size != 0) {
    free(block->data);
    block->size = 0;
  }
}
