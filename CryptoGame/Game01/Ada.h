#pragma once

class Ada
{
public:
   // Initialize the variables
   Ada();

   // Sets the sprite clips in the right order
   void setSpriteClips();

   // Render ada relative to the character
   void render(Window* window, Textures* textures, int camX, int camY, int animation);

   // Get the character's current positions and sprite animation
   int getAdaPosX();
   int getAdaPosY();
   void setAdaPosX(int positionXToSet);
   void setAdaPosY(int positionYToSet);
   bool getAdaActive();
   void setAdaActive(bool activeFlag);

private:
   // Currect Ada position
   int posX, posY;

   // Sprite animation clips in SDL_Rect. We will store them all in array and
   // render the one we need at a particular time
   SDL_Rect spriteClips[16];

   // Ada was innitialized by the player flag
   bool adaActive;
};