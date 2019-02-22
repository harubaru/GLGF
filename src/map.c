#include <map.h>

map_t *map_parse(char *filename)
{
	map_t *map = malloc(sizeof(map_t));
	tile_t *ptiles;
	light_tile_t *plights;
	FILE *fp = fopen(filename, "rb");
	if (!fp) {
		fprintf(stderr, "Cannot open file! - %s\n", filename);
		return NULL;
	}

	meta_t metadata;
	fread(&metadata, sizeof(meta_t), 1, fp);

	if (metadata.identifier != MAP_IDENT) {
		fprintf(stderr, "Map has wrong identifier! - %s\n", filename);
		return NULL;
	}

	ptiles = malloc(sizeof(tile_t) * metadata.numtiles);
	plights = malloc(sizeof(light_tile_t) * metadata.numlights);
	fread(ptiles, sizeof(tile_t), metadata.numtiles, fp);
	fread(plights, sizeof(light_tile_t), metadata.numlights, fp);

	map->metadata = metadata;
	map->tiles = ptiles;
	map->lights = plights;

	return map;
}

void map_write(char *filename, map_t *map)
{
	if ((!map) || (!filename))
		return;
	
	FILE *fp = NULL;
	if(!(fp = fopen(filename, "wb"))) {
		fprintf(stderr, "Failed to write to map! - Can't open file\n");
		return;
	}

	map->metadata.identifier = MAP_IDENT;
	map->metadata.version = MAP_VERSION_BETA;

	fwrite(&map->metadata, sizeof(meta_t), 1, fp);
	fwrite(map->tiles, sizeof(tile_t) * map->metadata.numtiles, 1, fp);
	fwrite(map->lights, sizeof(light_tile_t) * map->metadata.numlights, 1, fp);
}

static int tile_comp(const void *tile1, const void *tile2)
{
	tile_t *a = (tile_t *)tile1;
	tile_t *b = (tile_t *)tile2;
	if (a->z_order > b->z_order) return 1;
	if (a->z_order < b->z_order) return -1;
	return 0;
}

static int light_tile_comp(const void *tile1, const void *tile2)
{
	light_tile_t *a = (light_tile_t *)tile1;
	light_tile_t *b = (light_tile_t *)tile2;
	if (a->z_order > b->z_order) return 1;
	if (a->z_order < b->z_order) return -1;
	return 0;
}

void map_sort_z_index(map_t *map)
{
	if (!map)
		return;
	if ((!map->tiles) || (!map->lights))
		return;
	
	qsort(map->tiles, map->metadata.numtiles, sizeof(tile_t), tile_comp);
	qsort(map->lights, map->metadata.numlights, sizeof(light_tile_t), light_tile_comp);
}

void map_destroy(map_t *map)
{
	if (!map) {
		return;
	} else {
		if ((!map->tiles) || (!map->lights))
			return;
	}

	free(map->lights);
	free(map->tiles);
	free(map);
}
