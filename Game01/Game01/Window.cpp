#include "Main.h"
#include "Window.h"

Window::Window()
{
   // Initialize the window data
   window = NULL;
   renderer = NULL;
}

void Window::initialize()
{
   // Initialize SDL
   if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
      std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
      exit(1);
   }
   // Create window
   window = SDL_CreateWindow("CryptoGAME", 100, 200, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
   if (window == nullptr) {
      std::cout << "Failed to create window : " << SDL_GetError() << std::endl;
      SDL_DestroyWindow(window);
      exit(1);
   }
   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
   if (renderer == nullptr) {
      std::cout << "Failed to create renderer : " << SDL_GetError() << std::endl;
      SDL_DestroyWindow(window);
      SDL_DestroyRenderer(renderer);
      exit(1);
   }

   SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
   // Set the background color to black
   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
   SDL_RenderClear(renderer);
   SDL_RenderPresent(renderer);
}

void Window::cleanup()
{
   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderer);
}