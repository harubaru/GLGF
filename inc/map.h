#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <linmath.h>

#define FTMFIDENT (('F' << 24) + ('M' << 16) + ('T' << 8) + 'F') 

typedef struct meta {
    uint32_t identifier;
    uint32_t version;
    uint32_t numtiles;
    uint32_t properties;
} meta_t;

typedef struct lightdata {
    vec3 ambient;
    float intensity;
} lightdata_t;

typedef struct tile {
//  uint8_t texid;
    uint32_t texid;
    uint32_t x;
    uint32_t y;
//  uint16_t w;
//  uint16_t h;
    uint32_t properties;
} tile_t;

typedef struct map {
    meta_t metadata;
    tile_t *tiles;
} map_t;

map_t *map_parse(char *filename);
void map_destroy(map_t *map);

#endif
