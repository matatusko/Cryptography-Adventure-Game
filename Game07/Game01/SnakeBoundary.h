#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_mixer.h>

class SnakeBoundary
{
	friend class SnakeGame;

	SnakeBoundary();

private:
	SDL_Rect boundary;
	void setBoundary();
	void drawBoundary(SDL_Renderer* m_pRenderer);
};

SnakeBoundary::SnakeBoundary()
{
	setBoundary();
}

void SnakeBoundary::setBoundary()
{
	boundary.w = 1105;
	boundary.h = 665;
	boundary.x = 25;
	boundary.y = 25;
}

void SnakeBoundary::drawBoundary(SDL_Renderer* m_pRenderer)
{
	SDL_SetRenderDrawColor(m_pRenderer, 150, 50, 250, 80);
	SDL_RenderDrawRect(m_pRenderer, &boundary);
}


