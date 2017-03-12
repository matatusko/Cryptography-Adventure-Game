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
      void handleEvents(SDL_Event &e, Textures* textures);

      // Move the character
      void collisionCheck(Textures* textures);

      void setSpriteClips();

      // Render the dot relative to the camera
      void render(Window* window, Textures* textures, int camX, int camY, int animation);

      // Get the character's current positions and sprite animation
      int getPosX();
      int getPosY();
      void setPlayerPosX(int positionXToSet);
      void setPlayerPosY(int positionYToSet);
      int getCurrentClip();
      bool getCharacterMoving();
      Location getCurrentLocation();

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

      // Location where the player currently is
      Location currentLoc;
};