#pragma once

class Morse
{
public:
   Morse(int x, int y, int sprite);

   //Handles mouse event
   void handleEvent(SDL_Event* e);

   //Shows button sprite
   void render(Window* window, Textures* textures);

   //Returns pressed state
   bool isPressed();

   //Resets press state
   void resetPress();

private:
   //Top left position
   SDL_Point mPosition;

   //Currently used global sprite
   int mCurrentSprite;
   int mLastSprite;
   int hoversprite;
   int presssprite;

   bool pressed;
};