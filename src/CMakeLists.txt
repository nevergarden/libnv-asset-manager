add_library(nv-memory SHARED nv-memory.c)
set_target_properties(nv-memory PROPERTIES
  VERSION 1.0.0
  SOVERSION 1
  PUBLIC_HEADER nv-memory.h
)
