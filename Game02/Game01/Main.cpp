#include "Main.h"

int main(int argc, char* argv[])
{
   Window window;
   Textures textures;
   window.initialize();

   if (!loadMedia(&textures, &window)) {
      std::cout << "Failed loading media. Terminating program." << std::endl;
   }
   else {
      gameLoop(&textures, &window);
   }

   window.cleanup();
   return 0;
}

bool loadMedia(Textures *textures, Window *window)
{
   // Set success flag
   bool success = true; 

   // Load the background texture
   if (!(textures->background.loadFromFile("objects/map.png", window))) {
      std::cout << "Failed to load the map texture" << std::endl;
      success = false;
   }

   // Load the character texture
   if (!(textures->character.loadFromFile("objects/character.png", window))) {
      std::cout << "Failed to load the character texture" << std::endl;
      success = false;
   }

   return success;
}

void gameLoop(Textures* textures, Window* window)
{
   // Game loop flag
   bool gameRunning = true;
   
   // Initialize main character
   Character character;

   // Create the camera rectangle at position 0, 0 with camera's features
   SDL_Rect camera = { 0, 0, CAMERA_WIDTH, CAMERA_HEIGHT };

   // Initialize Event handler
   SDL_Event e;

   // Initialize the frames for rendering animations
   int currentFrame, currentAnimation = 0;

   // Start the game loop
   while (gameRunning) {

      // Handle the main game events on queue
      while (SDL_PollEvent(&e) != 0) {
         // Check for quit signal
         if (e.type == SDL_QUIT) {
            gameRunning = false;
         }
         // Handle the character events
         character.handleEvents(e);
      }

      // Move and animate the character
      character.move();
      currentAnimation = animateCharacter(&character);

      // Center the camera with the focus on the character and keep it in bounds of the map
      cameraFocus(&camera, &character);

      // Clear screen
      SDL_SetRenderDrawColor(window->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(window->renderer);

      // Render background clipped to the camera screen
      textures->background.render(window, 0, 0, &camera);

      // Render character
      character.render(window, textures, camera.x, camera.y, currentAnimation);

      // Update screen
      SDL_RenderPresent(window->renderer);

      SDL_Delay(75);
   }
}

void cameraFocus(SDL_Rect* camera, Character* character)
{
   // Center the camera over the character 
   camera->x = (character->getPosX() + CHARACTER_WIDTH / 2) - CAMERA_WIDTH / 2;
   camera->y = (character->getPosY() + CHARACTER_HEIGHT / 2) - CAMERA_HEIGHT / 2;
   
   // Prevent the camera from leaving the map screen
   if (camera->x < 0) {
      camera->x = 0;
   }
   if (camera->y < 0) {
      camera->y = 0;
   }
   if (camera->x > MAP_WIDTH - camera->w) {
      camera->x = MAP_WIDTH - camera->w;
   }
   if (camera->y > MAP_HEIGHT - camera->h) {
      camera->y = MAP_HEIGHT - camera->h;
   }
}

int animateCharacter(Character* character) {

   static int frameChange = 0;
   int currentFrame = character->getCurrentClip();
   // Checks if the character is moving, and if it is increases the current movement state by +1
   // up to 4 times, when it returns back to the original when the key is pressed up
   if (character->getCharacterMoving()) {
      frameChange++;
      if (frameChange >= 8) {
         frameChange = 0;
      }
      currentFrame += frameChange / 2;
   }

   return currentFrame;
}