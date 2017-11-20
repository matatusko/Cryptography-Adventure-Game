#pragma once

class Alphabet
{
public:
   Alphabet(int x, int y, int sprite);

   void handleEvents(SDL_Event* e);

   void render(Window* window, Textures* textures);

   int getCurrentSprite();

   void setCurrentSprite(int x);

private:
   SDL_Point position;

   int currentSprite;
};