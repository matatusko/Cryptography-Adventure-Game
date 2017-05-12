#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
using namespace std;

class SnakeTexture {

	friend class SnakeGame;

	SnakeTexture(const std::string &fileName);

private:

	SDL_Surface* pTempSurface = NULL;
	SDL_Texture* m_pTexture = NULL;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;

	void loadImage(const std::string &fileName);
	void createTexture(SDL_Renderer* m_pRenderer);
	void getDimensions();
	void setRectangle();
	void drawTexture(SDL_Renderer* m_pRenderer);
	void destroyTexture();
	void setPos(int one, int two);

};

SnakeTexture::SnakeTexture(const std::string &fileName)
{
	loadImage(fileName);
}

void SnakeTexture::loadImage(const std::string &fileName)
{
	pTempSurface = SDL_LoadBMP(fileName.c_str());
}

void SnakeTexture::createTexture(SDL_Renderer* m_pRenderer)
{
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
}

void SnakeTexture::getDimensions()
{
	SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
}

void SnakeTexture::setPos(int one, int two)
{
	m_destinationRectangle.x = one;
	m_destinationRectangle.y = two;
}

void SnakeTexture::setRectangle()
{
	m_sourceRectangle.x = 0;
	m_sourceRectangle.y = 0;
	m_destinationRectangle.w = m_sourceRectangle.w;
	m_destinationRectangle.h = m_sourceRectangle.h;
}

void SnakeTexture::drawTexture(SDL_Renderer* m_pRenderer)
{
	SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
}

void SnakeTexture::destroyTexture()
{
	SDL_DestroyTexture(m_pTexture);
}


