#ifndef _NV_IMAGE_ASSET_H
#define _NV_IMAGE_ASSET_H
#include "nv-asset-manager.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STBI_NO_BMP
#define STBI_NO_TGA
#define STBI_NO_PSD
#define STBI_NO_HDR
#define STBI_NO_PIC
#define STBI_NO_GIF
#define STBI_NO_PNM
#endif

typedef struct nv_texture_info_t {
  int32_t id;
  int x, y, depth;
} nv_texture_info_t;

nv_texture_info_t load_texture(const char * path, nv_memory_block_t * block, nv_asset_map_t * map);

#endif
