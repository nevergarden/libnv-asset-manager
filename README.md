# libnv-asset-manager
A simple asset manager with a memory pool allocated for games.
For now the whole concept of allocating a memory pool must be done manualy but
with an archive this system is gonna become automatic and also game can be
data driven in this case.  
This project started as a memory allocator but turned into an asset manager
since memory management should be carefuly written, therefore some basic
pool allocations are required.

# Public API
## Allocation
The main allocation functions are `nv_malloc` and `nv_free`. The purpose of
these functions are to load a whole required scene assets. So when we load
the scene this allocations are called and when we unload it's freed
completely.

To use include the public header:
```c
#include <nv-asset-manager.h>
```

```c
// allocates 4kb of memory pool to block.
nv_memory_block_t block;
nv_malloc(4096, &block);
// frees that block
nv_free(&block);
```

## Map of Assets , Push, Pop and Get
So in order to keep track of our assets we need a map which is dynamicly
allocated in memory and it's size increases on each push.

To initialize a map:
```c
nv_memory_block_t block;
nv_asset_map_t * map = init_asset_map(&block);
// ... Do stuff
nv_free_asset_map(map);
```
Now we can push data buffers into block and keep their id.
```c
// Push asset
const char * data = "Hello";
int32_t asset_id = nv_asset_manager_push(&block, map, data, strlen(data));
// Get Asset
mv_asset_block_t stuff;
nv_asset_manager_get(&block, map, asset_id, &stuff);
```
Try to use all these allocations in stack so just pass a simple stuff from
stack to it and don't allocate more.

Also there is a poping from stack that's not recommended to use but it frees
last pushed asset, so you can free that asset so you'll have more remaining
memory to push data to.
