#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <texturemanager.h>

#define TEX_LIMIT 0xFF

GLuint *texid_entries;
static size_t i = 0;

void texturemanager_init(char *resource_path)
{
	FILE *fp;
	char line[0xFF];
	
	if (!(fp = fopen(resource_path, "r"))) {
		fprintf(stderr, "Cannot load resource file - %s\n", resource_path);
		return;
	}

	texid_entries = calloc(1, sizeof(GLuint) * TEX_LIMIT);

	while (fgets(line, 0xFF, fp) != NULL) {
		if (i == TEX_LIMIT)
			break;
		texid_entries[i] = texture_create(line);
		i++;

	}
	
	fclose(fp);
}

GLuint texturemanager_getid(GLuint id)
{
	return texid_entries[id];
}

void texturemanager_destroy()
{
	size_t j;
	for (j = 0; j < i; j++)
		texture_destroy(texid_entries[j]);
	
	free(texid_entries);
}
