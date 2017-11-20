#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_mixer.h>
#include "SnakeDirection.h"
#include "SnakeBoundary.h"
#include "SnakeSnake.h"
#include "SnakeRandom.h"
#include "SnakeBackground.h"
#include "SnakeTexture.h"
#include "SnakeText.h"
#include "SnakeAudio.h"
#include <deque>
#include <iostream>
using namespace std;


class SnakeGame
{
public:

	SnakeGame(SDL_Window* window = NULL, SDL_Renderer* renderer = NULL);

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning = true;
	bool hexOne = false;
	bool octOne = false;
    bool complete[3];
    
	Snake snake;
	SnakeDirection direction;
	SnakeBoundary boundary;
	SnakeBackground background;
	SnakeAudio audio;
	SnakeText gameComplete;

	std::deque<SnakeTexture>   hexagonList;
	std::deque<SnakeTexture>   octagonList;
	std::deque<SnakeDirection> directionList;
	std::deque<SnakeText>      textList;
	
//	bool init(const char* title, int xpos, int ypos, int width, int height);
	void render();
	void update();
	void handleEvents(SDL_Event *e);
	void clean();
	void drawSnake();
	void drawHex(SDL_Renderer* m_pRenderer);
	void drawOct(SDL_Renderer* m_pRenderer);
	void drawText(SDL_Renderer* m_pRenderer);
    void createText();
	void getSurface();
	void getTexture(SDL_Renderer * m_pRenderer);
	void moveText(SDL_Renderer* m_pRenderer);
	void moveTextTwo(SDL_Renderer* m_pRenderer);
    void updateList();
	bool running();
	void boundaryCheckOne();
	void boundaryCheckTwo();
	void bodyCollision();
	void eatHexOne();
	void eatHexTwo();
	void eatOctOne();
	void eatOctTwo();
	void changeText();
	void changeOct();
	void createHex();
	void createOct();
	void reset();
	void resetSnake();
	void flash();
	void initComplete();
	void drawGameComplete();
	
};

SnakeGame::SnakeGame(SDL_Window* window, SDL_Renderer* renderer)
	:snake()
	, boundary()
	, direction(0, 1)
	, background()
	, audio()
	, gameComplete()
{
   m_pWindow = window;
   m_pRenderer = renderer;
	directionList.push_front(SnakeDirection(80, 80));
    background.createTexture(m_pRenderer);
	background.setRectangle();
    createHex();
    createOct();
    createText();
    getSurface();
	getTexture(m_pRenderer);
    moveText(m_pRenderer);
	moveTextTwo(m_pRenderer);
	initComplete();
	
	gameComplete.getFont(80);
	gameComplete.rect.y = 25;
	gameComplete.rect.w += 276 * 3;
	gameComplete.newText("Decryption complete", m_pRenderer);
}

/*
bool SnakeGame::init(const char* title, int xpos, int ypos, int width, int height)
{
 
	if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO) >= 0)
	{
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, 0);

		if (m_pWindow != 0)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		}
	}

	else { return false; }

	return true;
} */

void SnakeGame::render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);
	SDL_RenderClear(m_pRenderer);

	background.drawBackGround(m_pRenderer);
	boundary.drawBoundary(m_pRenderer);
	
	drawText(m_pRenderer);
	drawHex(m_pRenderer);
	drawOct(m_pRenderer);
	drawSnake();
	flash();
	drawGameComplete();
	
	SDL_RenderPresent(m_pRenderer);
}


void SnakeGame::update()
{   
    updateList();
    boundaryCheckOne();
    boundaryCheckTwo();
	bodyCollision();
	eatHexOne();
    eatHexTwo();
	eatOctOne();
	eatOctTwo();
}

void SnakeGame::handleEvents(SDL_Event* e)
{
   if (e->type == SDL_KEYDOWN) 
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			m_bRunning = false;
			break;

		case SDLK_DOWN:
			direction.set(0, 10);
			break;

		case SDLK_UP:
			direction.set(0, -10);
			break;

		case SDLK_RIGHT:
			direction.set(10, 0);
			break;

		case SDLK_LEFT:
			direction.set(-10, 0);
			break;

		}
	}
}

void SnakeGame::clean()
{
	background.destroyBackGround();
	audio.destroyAudio();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	IMG_Quit();
	SDL_Quit();
}

void SnakeGame::createHex()
{
	SnakeRandom random = SnakeRandom();
	hexagonList.push_front(SnakeTexture("hexagon.bmp"));
	hexagonList[0].createTexture(m_pRenderer);
	hexagonList[0].getDimensions();
	hexagonList[0].setPos(random.x, random.y);
	hexagonList[0].setRectangle();
}

void SnakeGame::createOct()
{
	SnakeRandom random = SnakeRandom();
	octagonList.push_front(SnakeTexture("logo2.bmp"));
	octagonList[0].createTexture(m_pRenderer);
	octagonList[0].setPos(random.x, random.y);
	octagonList[0].getDimensions();
	octagonList[0].setRectangle();
}

void SnakeGame::drawSnake()
{
	for (int i = 0; i<directionList.size(); i++)
	{
		snake.body.x = directionList.at(i).x;
		snake.body.y = directionList.at(i).y;
		SDL_SetRenderDrawColor(m_pRenderer, 150, 50, 250, 80);
		SDL_RenderFillRect(m_pRenderer, &snake.body);
	}

}

void SnakeGame::drawHex(SDL_Renderer* m_pRenderer)
{
	for (int i = 0; i<hexagonList.size(); i++)
	    hexagonList.at(i).drawTexture(m_pRenderer);
}

void SnakeGame::drawOct(SDL_Renderer* m_pRenderer)
{
	for (int i = 0; i<octagonList.size(); i++)
	    octagonList.at(i).drawTexture(m_pRenderer);
}

void SnakeGame::drawText(SDL_Renderer* m_pRenderer)
{   
	for (int i = 0; i < textList.size(); i++)
	{
		textList.at(i).drawText(m_pRenderer);
		textList.at(i).drawRect(m_pRenderer);
	}
}

void SnakeGame::createText()
{
	for (int i = 0; i<6; i++)
	    textList.push_front(SnakeText());
}

void SnakeGame::getSurface()
{
	textList.at(0).createSurface("A");
	textList.at(1).createSurface("14");
	textList.at(2).createSurface("12");
	textList.at(3).createSurface("24");
	textList.at(4).createSurface("HEX");
	textList.at(5).createSurface("OCT");
}

void SnakeGame::getTexture(SDL_Renderer * m_pRenderer)
{
	for (int i = 0; i<textList.size(); i++)
		textList.at(i).createTexture(m_pRenderer);
}

void SnakeGame::moveText(SDL_Renderer* m_pRenderer)
{
	for (int i = 0; i<4; i++) 
		textList.at(i).rect.x = 26 + i * 276;
}

void SnakeGame::moveTextTwo(SDL_Renderer* m_pRenderer)
{
	textList.at(4).rect.y -= 100;
	textList.at(5).rect.y -= 100;
	textList.at(5).rect.x += 276 * 2;
	textList.at(4).rect.w += 276;
	textList.at(5).rect.w += 276;
	textList.at(3).rect.w -= 1;
	textList.at(5).rect.w -= 1;
}

void SnakeGame::updateList()
{
	int x = direction.x + directionList[0].x;
	int y = direction.y + directionList[0].y;
	directionList.push_front(SnakeDirection(x, y));
}

void SnakeGame::boundaryCheckOne()
{
    for (int i = 0; i < 10; i++)
	    if (directionList[0].x + (i) == boundary.boundary.x || directionList[0].y + (i) == boundary.boundary.y)
		    resetSnake();
}

void SnakeGame::boundaryCheckTwo()
{
	for (int i = 0; i < 10; i++)
	    if (directionList[0].x + (i) == boundary.boundary.x + boundary.boundary.w || directionList[0].y + (i) == boundary.boundary.y + boundary.boundary.h - 200)
	        resetSnake();
}

void SnakeGame::resetSnake()
{   
	initComplete();
	audio.playOne();
	reset();
	directionList.clear();
	SnakeRandom r1 = SnakeRandom();
	directionList.push_front(SnakeDirection(r1.x, r1.y));
}

void SnakeGame::bodyCollision()
{
	int topX = directionList[0].x;
	int topY = directionList[0].y;

	for (int i = 1; i<directionList.size(); i++)
	    if (directionList.at(i).x == topX && directionList.at(i).y == topY)
		    resetSnake();
}

void SnakeGame::eatHexOne()
{
	for (int i = 0; i <50; i++)
		if (directionList[0].x + (i) <= hexagonList[0].m_destinationRectangle.x && directionList[0].y + (i) >= hexagonList[0].m_destinationRectangle.y)
		{   
			audio.playTwo();
			hexagonList.clear();
			createHex();
			changeText();
			hexOne = true;
		}
}

void SnakeGame::eatHexTwo()
{
	for (int i = 0; i <50; i++)
		if (directionList[0].x - (i) <= hexagonList[0].m_destinationRectangle.x && directionList[0].y - (i) >= hexagonList[0].m_destinationRectangle.y)
		{   
			audio.playTwo();
			hexagonList.clear();
			createHex();
			changeText();
			hexOne = true;
		}
}

void SnakeGame::changeText()
{
	if (!hexOne)
	{
		textList[0].newText("A = 10", m_pRenderer);
		complete[0] = true;
	}

	else if (hexOne)
	{
		textList[1].newText("14 = 20", m_pRenderer);
		complete[1] = true;
	}
}

void SnakeGame::eatOctOne()
{
	for (int i = 0; i <50; i++)
		if (directionList[0].x + (i) <= octagonList[0].m_destinationRectangle.x && directionList[0].y + (i) >= octagonList[0].m_destinationRectangle.y)
		{
			octagonList.clear();
			createOct();
			changeOct();
			octOne = true;
		}
}

void SnakeGame::eatOctTwo()
{
	for (int i = 0; i <50; i++)
		if (directionList[0].x - (i) <= octagonList[0].m_destinationRectangle.x && directionList[0].y - (i) >= octagonList[0].m_destinationRectangle.y)
		{
			octagonList.clear();
			createOct();
			changeOct();
			octOne = true;
		}
}

void SnakeGame::changeOct()
{
	if (!octOne)
	{
		textList[2].newText("12 = 10", m_pRenderer);
		complete[2] = true;
	}

	else if (octOne)
	{
		textList[3].newText("24 = 20", m_pRenderer);
		complete[3] = true;
	}
}

void SnakeGame::reset()
{
	hexOne = false;
	octOne = false;
	textList[0].newText("A",  m_pRenderer);
	textList[1].newText("14", m_pRenderer);
	textList[2].newText("12", m_pRenderer);
	textList[3].newText("24", m_pRenderer);
}

void SnakeGame::flash()
{
	if (hexOne)
	{
		textList[4].setColor(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
		textList[4].newText("HEX", m_pRenderer);
	}
	
	if (octOne)
	{
		textList[5].setColor(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
		textList[5].newText("OCT", m_pRenderer);
	}
}

void SnakeGame::initComplete()
{   
	for(int i = 0; i<4; i++)
	    complete[i] = false;
}

void SnakeGame::drawGameComplete()
{
	if (complete[0] == true && complete[1] == true && complete[2] == true && complete[3])
	{   
		hexagonList.clear();
		gameComplete.drawText(m_pRenderer);
	}

}

bool SnakeGame::running()
{
	return m_bRunning;
}




