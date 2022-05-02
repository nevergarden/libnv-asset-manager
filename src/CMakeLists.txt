add_library(nv-asset-manager SHARED nv-asset-manager.c nv-image-asset.c)
# TODO: this should not be included with msvc
target_link_libraries(nv-asset-manager PUBLIC m)
set_target_properties(nv-asset-manager PROPERTIES
  VERSION 0.0.1
  SOVERSION 1
  PUBLIC_HEADER nv-asset-manager.h
)
