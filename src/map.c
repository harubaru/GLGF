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

	if (metadata.identifier != FTMFIDENT) {
		fprintf(stderr, "Map has wrong identifier! - %s\n", filename);
		return NULL;
	}

	ptiles = malloc(sizeof(tile_t) * metadata.numtiles);
	fread(ptiles, sizeof(tile_t), metadata.numtiles, fp);

	map->metadata = metadata;
	map->tiles = ptiles;

	return map;
}

void map_destroy(map_t *map)
{
	if (map) {
		free(map->tiles);
		free(map);
	}
}
