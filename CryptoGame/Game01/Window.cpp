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
   if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
      std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
      exit(1);
   }
   // Set texture filtering to linear
   if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
   }
   /* Create an SDL window with the following parameters: */
   /*    - title of the window */
   /*    - starting position of the window (in this case we let the operating system do it for us) */
   /*    - width and height of the window */
   /*    - flag which defines the window features (border, fullscreen etc) */
   window = SDL_CreateWindow("CryptoGAME", 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED,
            CAMERA_WIDTH, 
            CAMERA_HEIGHT, 
            SDL_WINDOW_RESIZABLE);
   if (window == NULL) {
      std::cout << "Failed to create window : " << SDL_GetError() << std::endl;
      exit(1);
   }
   /* Create a renderer with the following paramenters: */
   /*    - window, to which renderer will apply */
   /*    - index, set to -1 which means to use a driver which supports the renderer */
   /*    - flags which define the renderer features (in this case accelerated with synchronized display refresh rate */
   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   if (renderer == NULL) {
      std::cout << "Failed to create renderer : " << SDL_GetError() << std::endl;
      SDL_DestroyWindow(window);
      exit(1);
   }
   // Initialize SDL_Image
   int imgFlags = IMG_INIT_PNG;
   if (!(IMG_Init(imgFlags) & imgFlags)) {
      std::cout << "Failed to initialize SDL_image : " << IMG_GetError() << std::endl;
      SDL_DestroyWindow(window);
      SDL_DestroyRenderer(renderer);
      exit(1);
   }
   // Initialize SDL_TTF
   if (TTF_Init() == -1) {
      std::cout << "Failed to initialize SDL_TTD : " << TTF_GetError() << std::endl;
      SDL_DestroyWindow(window);
      SDL_DestroyRenderer(renderer);
      exit(1);
   }
}

void Window::cleanup()
{
   // Destroy the windows
   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderer);

   // Quit SDL
   IMG_Quit();
   SDL_Quit();
}