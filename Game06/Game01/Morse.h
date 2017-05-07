#pragma once

class Morse
{
public:
   Morse(int x, int y, int sprite);

   void handleEvents(SDL_Event* e);

   void render(Window* window, Textures* textures);

private:
   SDL_Point position;

   int currentSprite, lastSprite, coloredSprite;
};