#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

class SnakeText
{
	friend class SnakeGame;

	SnakeText();

private:

	TTF_Font * font = NULL;
	SDL_Color colour;
	SDL_Surface * surface = NULL;
	SDL_Texture * texture = NULL;
	SDL_Rect rect;

	void getFont(int num);
	void setColor(Uint8 one, Uint8 two, Uint8 three, Uint8 four);
	void createSurface(const char *text);
	void createTexture(SDL_Renderer * m_pRenderer);
	void setRect();
	void drawText(SDL_Renderer * m_pRenderer);
	void drawRect(SDL_Renderer * m_pRenderer);
	void newText(const char *text, SDL_Renderer * m_pRenderer);
};

SnakeText::SnakeText()
{
	getFont(80);
	setColor(100, 100, 100, 100);
	setRect();
}

void SnakeText::getFont(int num)
{
	TTF_Init();
	font = TTF_OpenFont("regular.ttf", 80);
}

void SnakeText::setColor(Uint8 one, Uint8 two, Uint8 three, Uint8 four)
{
	colour = { one, two, three, four };
}

void SnakeText::createSurface(const char *text)
{
	surface = TTF_RenderText_Solid(font, text, colour);
}

void SnakeText::createTexture(SDL_Renderer * m_pRenderer)
{
	texture = SDL_CreateTextureFromSurface(m_pRenderer, surface);
}

void SnakeText::setRect()
{
	rect.x = 26;
	rect.y = 589;
	rect.w = 276;
	rect.h = 100;
}

void SnakeText::drawText(SDL_Renderer * m_pRenderer)
{   
	SDL_RenderCopy(m_pRenderer, texture, NULL, &rect);
}

void SnakeText::drawRect(SDL_Renderer * m_pRenderer)
{
	SDL_SetRenderDrawColor(m_pRenderer, 150, 50, 250, 80);
	SDL_RenderDrawRect(m_pRenderer, &rect);
}

void SnakeText::newText(const char *text, SDL_Renderer * m_pRenderer)
{
	SDL_FreeSurface(surface);
    createSurface(text);
	createTexture(m_pRenderer);
}



