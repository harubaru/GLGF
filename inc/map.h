#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <linmath.h>

#define MAP_IDENT (('F' << 24) + ('M' << 16) + ('T' << 8) + 'F') 
#define MAP_VERSION_BETA (('A' << 24) + ('T' << 16) + ('E' << 8) + 'B')

typedef struct meta {
	uint32_t identifier;
	uint32_t version;
	uint32_t numtiles;
	uint32_t numlights;
	uint32_t properties;
} meta_t;

typedef struct tile {
	uint16_t texid;
	uint8_t z_order;
	uint8_t properties;
	uint32_t x;
	uint32_t y;
	uint16_t w;
	uint16_t h;
} tile_t;

typedef struct light_tile {
	uint8_t z_order;
	uint8_t properties;
	uint32_t x;
	uint32_t y;
	uint16_t w;
	uint16_t h;
	uint8_t r;
	uint8_t g;
	uint8_t b;
} light_tile_t;

typedef struct map {
	meta_t metadata;
	tile_t *tiles;
	light_tile_t *lights;
} map_t;

map_t *map_parse(char *filename);
void map_write(char *filename, map_t *map);
void map_sort_z_index(map_t *map);
void map_destroy(map_t *map);

#endif
