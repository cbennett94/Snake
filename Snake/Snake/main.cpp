#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Snake.h"
#include <Windows.h>

const int SCREEN_WIDTH = 50;
const int SCREEN_HEIGHT = 50;
const int SCALE_X = 4;
const int SCALE_Y = 4;
int direction = 0;
std::vector<int> food;
int score = 0;

void clearScreen(SDL_Renderer* renderer);
bool simulateStep(Snake& play, int** grid, int** temp);
void setPixels(SDL_Renderer* renderer, int** grid);
std::vector<int> randomFood(Snake play);

int main()
{
	Snake player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	food= randomFood(player);
	int** grid = new int* [SCREEN_HEIGHT];
	int** temp = new int* [SCREEN_HEIGHT];
	for (int i = 0; i < SCREEN_HEIGHT; i++)
		temp[i] = new int[SCREEN_WIDTH];
	for (int i = 0; i < SCREEN_HEIGHT; i++)
		grid[i] = new int[SCREEN_WIDTH];
	grid[player.getHeadX()][player.getHeadY()] = 1;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(SCALE_X * SCREEN_WIDTH, SCALE_Y * SCREEN_HEIGHT, 0, &window, &renderer);
	SDL_RenderSetScale(renderer, SCALE_X, SCALE_Y);
	surface = SDL_GetWindowSurface(window);

	clearScreen(renderer);
	setPixels(renderer, grid);

	SDL_Event e;
	bool quit = false;
	while (quit == false)
	{
		quit = simulateStep(player, grid, temp);
		setPixels(renderer, grid);
		SDL_Delay(100);
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					direction = 3;
					break;
				case SDLK_RIGHT:
					direction = 2;
					break;
				case SDLK_UP:
					direction = 1;
					break;
				case SDLK_DOWN:
					direction = 0;
					break;
				default:
					break;
				}
			}
		}
	}
	return 0;
}

void clearScreen(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

bool simulateStep(Snake& play, int** grid, int** temp)
{
	//update the coordinates of the snake
	play.UpdateBody(direction);
	//determine if you are on a food
	if (play.getHeadX() == food[0] && play.getHeadY() == food[1])
	{
		food = randomFood(play);
		play.grow();
		score++;
	}
	//determine if the snake is out of bounds
	if (play.getHeadX() >= SCREEN_WIDTH || play.getHeadX() < 0
		|| play.getHeadY() >= SCREEN_HEIGHT || play.getHeadY() < 0)
	{
		std::cout << "You went out of bounds. Your score = " << score;
		return true;
	}
	//determine if the snake is hitting itself
	if (play.SelfCollide())
	{
		std::cout << "You self collided. Your score = " << score;
		return true;
	}
	//determine cell states
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			temp[i][j] = 0;
		}
	}
	std::vector<std::vector<int>> toLight = play.getBody();
	for (int i = 0; i < toLight.size(); i++)
	{
		temp[toLight[i][0]][toLight[i][1]] = 1;
	}
	temp[food[0]][food[1]] = 1;
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			grid[i][j] = temp[i][j];
		}
	}
	return false;
}

void setPixels(SDL_Renderer* renderer, int** grid)
{
	clearScreen(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int k = 0; k < SCREEN_HEIGHT; k++)
		{
			if (grid[i][k] == 1)
				SDL_RenderDrawPoint(renderer, i, k);
		}
	}
	SDL_RenderPresent(renderer);
}

std::vector<int> randomFood(Snake play)
{
	srand(time(NULL));
	std::vector<int> cord;
	int randX = rand() % (SCREEN_WIDTH - 1) + 1;
	int randY = rand() % (SCREEN_HEIGHT - 1) + 1;
	if (randX == play.getHeadX() && randY == play.getHeadY())
	{
		cord = randomFood(play);
	}
	else
	{
		cord.push_back(randX);
		cord.push_back(randY);
	}
	return(cord);
}