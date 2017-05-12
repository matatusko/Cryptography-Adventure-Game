#include <iostream>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_mixer.h>

class SnakeRandom
{
	friend class SnakeGame;

public:
	SnakeRandom();
private:
	int x;
	int y;
	void generate();
};

SnakeRandom::SnakeRandom()
{
	generate();
}

void SnakeRandom::generate()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(100, 400);
	x = distr(eng);
	y = distr(eng);
}


