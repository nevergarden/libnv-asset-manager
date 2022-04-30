#include "nv-memory.h"
#include <stdlib.h>
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

nv_memory_status_t nv_malloc(size_t size, nv_memory_block_t * block) {
  if(size == 0)
    return bad_allocation;

  if(MEMALIGN(&block->data, get_page_size(), size))
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

#undef MEMALIGN
