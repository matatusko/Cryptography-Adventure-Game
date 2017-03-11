#pragma once
#include "Main.h"

class Window
{
   public:
      // Constructor - Intialize internals
      Window();

      // Create window and renderer
      void initialize();

      // Cleanup the memory from all the SDL stuff
      void cleanup();

      // Window data
      SDL_Window* window;
      SDL_Renderer* renderer;
};