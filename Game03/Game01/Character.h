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

      // Sets the sprite clips in the right order
      void setSpriteClips();

      // Render the dot relative to the camera
      void render(Window* window, Textures* textures, int camX, int camY, int animation);

      // Get the character's current positions and sprite animation
      int getPosX();
      int getPosY();
      void setPlayerPosX(int positionXToSet);
      void setPlayerPosY(int positionYToSet);
      bool getCharacterMoving();
      Direction getCurrentDirection();
      Location getCurrentLocation();

   private:
      // Currect character position
      int posX, posY;

      // The current movement of the character
      int velX, velY;

      // Sprite animation clips in SDL_Rect. We will store them all in array and
      // render the one we need at a particular time
      SDL_Rect spriteClips[16];

      // Character is currently moving flag
      bool characterMoving;

      // Location where the player currently is
      Location currentLoc;
      Direction currentDirection;
};