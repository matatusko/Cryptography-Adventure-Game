#pragma once
#include "Main.h"
#include "Window.h"
#include "Texture.h"
#include "Character.h"
#include "npc.h"

class Npc {
   public:
      // Initialize the variables
      Npc(int positionX, int posionY, int npcSprite);

      // Render the NPC in the correct position with the correct sprite
      void render(Window* window, Textures* textures, int camX, int camY);

      SDL_Rect getLocation();

   private:
      // Current npc position
      int posX, posY;

      // This NPC's sprite
      int npcSprite;

      // NPC full location
      SDL_Rect location;
};