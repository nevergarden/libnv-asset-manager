#include <nv-memory.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  long page_size = sysconf(_SC_PAGESIZE);

  nv_memory_block_t block;
  nv_malloc(10, &block);
  if(block.size % page_size != 0 && block.size == 0)
    return -1;
  nv_free(&block);

  if(nv_malloc(0, &block) != bad_allocation)
    return -1;
  if(block.size != 0)
    return -1;
  nv_free(&block);

  nv_malloc(page_size, &block);
  printf("%d\n", block.size);
  if(block.size != page_size)
    return -1;

  return 0;
}
