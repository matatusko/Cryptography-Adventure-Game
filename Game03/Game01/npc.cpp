#include "Main.h"
#include "npc.h"

// Constructor sets the current NPC location and it's sprite
Npc::Npc(int positionX, int positionY, int sprite)
{
   posX = positionX;
   posY = positionY;
   npcSprite = sprite;

   // I honestly have no idea why this location rectangle has to be set like this
   // but it didn't work any other way properly ? O_o
   location = { posX + 32, posY + 32, -1, -1};
}

void Npc::render(Window* window, Textures* textures, int camX, int camY)
{
   textures->npc.render(window, posX - camX, posY - camY, &(textures->NPCspritesAvailable[npcSprite]));
}

SDL_Rect Npc::getLocation()
{
   return location;
}

