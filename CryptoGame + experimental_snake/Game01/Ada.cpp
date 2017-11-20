#include "Main.h"
#include "Ada.h"

Ada::Ada() 
{
   // Initialize the variables upon the Ada creation
   posX = 704;
   posY = 360;
   adaActive = false;

   // Cut the sprite sheet into correct positions
   setSpriteClips();
}

void Ada::render(Window* window, Textures* textures, int camX, int camY, int animation)
{
   // Ada rendeding function is very similar to the character as well
   textures->ada.render(window, posX - camX, posY - camY, &spriteClips[animation]);
}

void Ada::setSpriteClips()
{
   // Since Ada spritesheet is exactly the same as player sprite sheet, I'm cutting in
   // in exactly the same way into 16 different rectangles
   for (int y = 0, curr = 0; y < 4; y++) {
      for (int x = 0; x < 4; x++, curr++)
      {
         spriteClips[curr].x = x * 32;
         spriteClips[curr].y = y * 32;
         spriteClips[curr].w = 32;
         spriteClips[curr].h = 32;
      }
   }
}

int Ada::getAdaPosX()
{
   return posX;
}

int Ada::getAdaPosY()
{
   return posY;
}

void Ada::setAdaPosX(int positionXToSet)
{
   posX = positionXToSet;
}

void Ada::setAdaPosY(int positionYToSet)
{
   posY = positionYToSet;
}

bool Ada::getAdaActive()
{
   return adaActive;
}

void Ada::setAdaActive(bool activeFlag)
{
   adaActive = activeFlag;
}