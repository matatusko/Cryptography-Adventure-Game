#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_mixer.h>
#define SIZE 20

class Snake
{
	friend class SnakeGame;

public:
	Snake();
private:
	SDL_Rect body;

	void createSnake();
	void setPosition();
};

Snake::Snake()
{
	createSnake();
	setPosition();
}

void Snake::createSnake()
{
	body.w = SIZE;
	body.h = SIZE;
}

void Snake::setPosition()
{
	body.x = 200;
	body.y = 200;
}



