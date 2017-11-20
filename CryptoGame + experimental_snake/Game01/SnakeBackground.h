#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
using namespace std;

class SnakeBackground
{

	friend class SnakeGame;

	SnakeBackground();

private:

	SDL_Surface* pTempSurface = NULL;
	SDL_Texture* m_pTexture = NULL;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;

	void loadImage();
	void createTexture(SDL_Renderer* m_pRenderer);
	void setRectangle();
	void drawBackGround(SDL_Renderer* m_pRenderer);
	void destroyBackGround();
};

SnakeBackground::SnakeBackground()
{
	loadImage();
}

void SnakeBackground::loadImage()
{
	pTempSurface = SDL_LoadBMP("background.bmp");
}

void SnakeBackground::createTexture(SDL_Renderer* m_pRenderer)
{
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
}

void SnakeBackground::setRectangle()
{
	m_destinationRectangle.x = m_sourceRectangle.x = 0;
	m_destinationRectangle.y = m_sourceRectangle.y = 0;
	m_destinationRectangle.w = m_sourceRectangle.w = 1280;
	m_destinationRectangle.h = m_sourceRectangle.h = 720;
}

void SnakeBackground::drawBackGround(SDL_Renderer* m_pRenderer)
{
	SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
}

void SnakeBackground::destroyBackGround()
{
	SDL_DestroyTexture(m_pTexture);
}

\
