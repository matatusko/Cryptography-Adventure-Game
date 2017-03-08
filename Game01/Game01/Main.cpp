#include "Main.h"

int main(int argc, char* argv[])
{
   Window window;
   window.initialize();

   SDL_Delay(1000);
   window.cleanup();
   return 0;
}