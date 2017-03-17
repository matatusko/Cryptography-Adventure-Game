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
   int next_x = 0, next_y = 0, current_index = 0;
   for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
         spriteClips[current_index].x = next_x;
         spriteClips[current_index].y = next_y;
         spriteClips[current_index].w = TILE_SIZE;
         spriteClips[current_index].h = TILE_SIZE;
         next_x += TILE_SIZE;
         current_index++;
      }
      next_x = 0;
      next_y += TILE_SIZE;
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