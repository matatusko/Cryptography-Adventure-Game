#pragma once
#include "Main.h"
#include "Window.h"
#include "Texture.h"

class Character
{
   public:
      // Initialize the variables
      Character();

      // Events related to character
      void handleEvents(SDL_Event &e);

      // Move the character
      void move();

      void setSpriteClips();

      // Render the dot relative to the camera
      void render(Window* window, Textures* textures, int camX, int camY, int animation);

      // Get the character's current positions and sprite animation
      int getPosX();
      int getPosY();
      int getCurrentClip();
      bool getCharacterMoving();

   private:
      // Currect character position
      int posX, posY;

      // The current movement of the character
      int velX, velY;

      // Sprite animation clips in SDL_Rect. We will store them all in array and
      // render the one we need at a particular time
      SDL_Rect spriteClips[16];

      // Current sprite clip to render
      int currentClip;

      // Character is currently moving flag
      bool characterMoving;
};