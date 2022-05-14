#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

int MAP_SIZE = 20;
char *map_filename = "map.txt";
#define CELL_SIZE 20

int **grid;

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
	read_map(map_filename);
}

int main() {

    return 0;
}
