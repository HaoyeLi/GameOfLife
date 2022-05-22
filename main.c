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
int get_cnt(int x, int y) {
	int cnt = 0;
	int direction[8][2] = {{-1, -1},
		{-1, 0},
		{-1, 1},
		{0,  -1},
		{0,  1},
		{1,  -1},
		{1,  0},
		{1,  1}};
	for (int i = 0; i < 8; i++) {
		int nx = x + direction[i][0];
		int ny = y + direction[i][1];
		if (nx < 0 || nx >= MAP_SIZE || ny < 0 || ny >= MAP_SIZE) {
			continue;
		}
		if (grid[nx][ny] == 1) {
			cnt++;
		}
	}
	return cnt;
}
void update_cells() {
	int **tmp = malloc(sizeof(int *) * MAP_SIZE);
	for (int i = 0; i < MAP_SIZE; i++) {
		tmp[i] = malloc(sizeof(int) * MAP_SIZE);
	}
	
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			tmp[i][j] = grid[i][j];
		}
	}
	
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			int cnt = get_cnt(i, j);
			if (grid[i][j] == 1) {
				if (cnt < 2 || cnt > 3) {
					tmp[i][j] = 0;
				}
			} else {
				if (cnt == 3) {
					tmp[i][j] = 1;
				}
			}
		}
	}
	memcpy(grid, tmp, sizeof(int *) * MAP_SIZE);
	
}

void show_map() {
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			printf("%d ", grid[i][j]);
		}
		printf("\n");
	}
}
int main() {
	init("config.txt");
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window *window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		MAP_SIZE * CELL_SIZE, MAP_SIZE * CELL_SIZE,
		SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Rect rect = {1, 1, MAP_SIZE * CELL_SIZE - 1, MAP_SIZE * CELL_SIZE - 1};
	show_map();
	while (1) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				save_map(map_filename);
				return 0;
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		render(renderer);
		SDL_RenderPresent(renderer);
		update_cells();
		show_map();
		SDL_Delay(1000);
	}
    return 0;
}
