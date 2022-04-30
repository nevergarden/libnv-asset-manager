#include <nv-memory.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

int main() {
  long page_size = sysconf(_SC_PAGESIZE);

  // Test 1: Normal check to see if we have memory block
  nv_memory_block_t block1;
  assert(nv_malloc(15, &block1) == ok);
  assert(block1.size == 15);
  nv_free(&block1);

  // Test 2: allocation of size zero must fail
  nv_memory_block_t block2;
  assert(nv_malloc(0, &block2) == bad_allocation);

  // Test 3: allocate more than a page
  nv_memory_block_t block3;
  assert(nv_malloc(page_size+1, &block3) == ok);
  assert(block3.size == page_size+1);
  nv_free(&block3);

  // Test 4: check memory freed and no memory leak
  nv_memory_block_t block4;
  assert(nv_malloc(12, &block4) == ok);
  strcpy(block4.data, "Hello World");
  assert(block4.size == 12);
  nv_free(&block4);
  assert(block4.size == 0);

  return 0;
}
