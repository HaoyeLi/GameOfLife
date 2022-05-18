#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

int MAP_SIZE = 20;
char *map_filename = "map.txt";
#define CELL_SIZE 20

int **grid;

void read_map(char *filename) {
	// 0000000000000
	
	FILE *fp = fopen(filename, "r");
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			char c;
			fscanf(fp, "%c ", &c);
			int val = atoi(&c);
			grid[i][j] = val;
		}
	}
}

void read_config(char *filename) {
	FILE *fp = fopen(filename, "r");
	fscanf(fp, "%d", &MAP_SIZE);
	printf("%d\n", MAP_SIZE);
	map_filename = malloc(sizeof(char) * 100);
	fscanf(fp, "%s", map_filename);
	fclose(fp);
}

void init(char *config_file) {
	read_config(config_file);
	
	grid = malloc(sizeof(int *) * MAP_SIZE);
	for (int i = 0; i < MAP_SIZE; i++) {
		grid[i] = malloc(sizeof(int) * MAP_SIZE);
		
	}
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			grid[i][j] = 0;
		}
	}
}

void show_map() {
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			printf("%d ", grid[i][j]);
		}
	}
}
int main() {

    return 0;
}
