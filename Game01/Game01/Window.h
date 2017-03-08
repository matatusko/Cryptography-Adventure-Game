#pragma once
#include "Main.h"

class Window
{
public:
   //Intializes internals
   Window();

   //Creates window
   void initialize();

   // Cleanup the SDL stuff
   void cleanup();

private:
   //Window data
   SDL_Window* window;
   SDL_Renderer* renderer;
};