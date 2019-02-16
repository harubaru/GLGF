#include <map.h>

map_t *map_parse(char *filename)
{
	map_t *map = malloc(sizeof(map_t));
	tile_t *ptiles;
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
	fread(ptiles, sizeof(tile_t), metadata.numtiles, fp);

	map->metadata = metadata;
	map->tiles = ptiles;

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
}

static int tile_comp(const void *tile1, const void *tile2)
{
	tile_t *a = (tile_t *)tile1;
	tile_t *b = (tile_t *)tile2;
	if (a->z_order > b->z_order) return 1;
	if (a->z_order < b->z_order) return -1;
	return 0;
}

void map_sort_z_index(map_t *map)
{
	if (!map)
		return;
	if (!map->tiles)
		return;
	
	qsort(map->tiles, map->metadata.numtiles, sizeof(tile_t), tile_comp);
}

void map_destroy(map_t *map)
{
	if (!map) {
		return;
	} else {
		if (!map->tiles)
			return;
	}

	free(map->tiles);
	free(map);
}
