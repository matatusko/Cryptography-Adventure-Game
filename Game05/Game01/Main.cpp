#include "Main.h"

int main(int argc, char* argv[])
{
   Window window;
   Textures textures;
   window.initialize();
   srand(time(NULL));

   if (!loadMedia(&textures, &window)) {
      std::cout << "Failed loading media. Terminating program." << std::endl;
   }
   else {
      gameLoop(&textures, &window);
   }

   window.cleanup();
   return 0;
}

void gameLoop(Textures* textures, Window* window)
{
   // Game loop flag and viewport render flag
   bool gameRunning = true;
   Interaction interactionFlag = Interaction::None;
   
   // Initialize main character
   Character character;
   int playerPositionX, playerPositionY;

   // Initialize Ada
   Ada ada;
   int adaPositionX, adaPositionY;
   int currentAdaDialog = 0;

   // Initialize Alphabet
   std::vector<Alphabet> railAlphabet;
   setAlphabetPositionForRail(textures, &railAlphabet);
   
   // Initialize Rail Cipher
   std::vector<Rail> rail;
   setRailSpritesPosition(textures, &rail);
   int currentRailDialog = 0;
   getAdaRailDialog(window, textures);

   // Initialize Caesar Cipher
   std::vector<Caesar> caesar;
   setCaesarSpritesPosition(textures, &caesar);

   // Create the camera rectangle at position 0, 0 with camera's features
   SDL_Rect camera = { 0, 0, CAMERA_WIDTH, CAMERA_HEIGHT };

   // Create the dialog window
   SDL_Rect dialogViewport = { 64, 64, 600, 150 };
   int dialogNumber;

   // Initialize Event handler
   SDL_Event e;

   // Initialize the frames for rendering animations
   int currentAnimation = 0;

   // Initialize the obstacles and their locatation
   std::vector<Obstacles> obstacles;
   setObstacles(&obstacles);

   // Initialie the NPC vector
   std::vector<Npc> npcs;
   setNpc(&npcs);

   // Start the game loop
   while (gameRunning) {

      // Get the current player and ada's position so if the collision happens they can return to the
      // position they were before the movement
      playerPositionX = character.getPosX();
      playerPositionY = character.getPosY();
      adaPositionX = ada.getAdaPosX();
      adaPositionY = ada.getAdaPosY();

      // Select the proper animation clip to render
      currentAnimation = animateCharacter(&character);

      // Handle the main game events on queue
      while (SDL_PollEvent(&e) != 0) {
         // Check for quit signal
         // automaticCollisions(e, &character);
         if (e.type == SDL_QUIT) {
            gameRunning = false;
         }
         if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && interactionFlag == Interaction::None) {
            interactionFlag = checkForInteraction(&character, &ada, npcs);
            dialogNumber = rand() % 6;
         }
         if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && interactionFlag == Interaction::AdaInitialization
            && e.key.repeat == 0) {
            currentAdaDialog++;
            if (currentAdaDialog > 3) {
               ada.setAdaActive(true);
               interactionFlag = Interaction::None;
            }
            if (currentAdaDialog == 2) {
               interactionFlag = Interaction::CaesarCipher;
            }
         }
         if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && interactionFlag == Interaction::RailDialog
            && e.key.repeat == 0) {
            currentRailDialog++;
            if (currentRailDialog == 5) {
               interactionFlag = Interaction::RailCipher;
            }
            if (currentRailDialog >= 8) {
               interactionFlag = Interaction::None;
            }
         }

         // Handle the mouse movement for rail cipher
         if (interactionFlag == Interaction::RailCipher) {
            for (int i = 0; i < 60; i++) {
               rail[i].handleEvents(&e);
            }
            for (int i = 0; i < railAlphabet.size(); i++) {
               railAlphabet[i].handleEvents(&e);
            }
         }
         // Handle the mouse movement for Caesar
         if (interactionFlag == Interaction::CaesarCipher) {
            for (int i = 0; i < 7; i++) {
               caesar[i].handleEvent(&e);
            }
         }

         // Handle the character movement and wall collisions
         character.handleMovement(e);
         character.CheckForWallCollisions(textures);

         // Move Ada right after the character and don't move it if the character is not moving
         // so she doesn't enter onto the character when he stops.
         // Ada only moves once she has been activated by character
         if (character.getCharacterMoving() && ada.getAdaActive()) {
            ada.setAdaPosX(playerPositionX);
            ada.setAdaPosY(playerPositionY);
         }

         // Check for collisions and if those happen return character right to their original positions
         // before collision happened
         if (character.getCurrentLocation() == Location::World) {
            checkForObjectsCollision(&character, &ada, obstacles, npcs, playerPositionX, playerPositionY,
               adaPositionX, adaPositionY);
         }
      }

      // Clear screen
      SDL_RenderClear(window->renderer);

      // Render the screen to the window depending on current location player is in
      if (character.getCurrentLocation() == Location::Home) {
         renderHome(window, textures, &camera);      
         // Render character
         character.render(window, textures, camera.x, camera.y, currentAnimation);
         ada.render(window, textures, camera.x, camera.y, currentAnimation);
      }
      else if (character.getCurrentLocation() == Location::World) {
         renderWorld(window, textures, &character, &ada, &camera, npcs, &currentAnimation);
      }

      // No interaction when character starts moving hence will kill the dialog window
      if (character.getCharacterMoving()) {
         interactionFlag = Interaction::None;
      }

      // Print the npc interaction dialog if found
      if (interactionFlag == Interaction::Npc) {
         textures->dialogBox.render(window, 50, 50);
         textures->npcDialogText[dialogNumber].render(window, 75, 75);
      }

      // Do the Ada initialization stuff
      if (interactionFlag == Interaction::AdaInitialization) {
         StartAdaInitializationEvent(window, textures, &ada, currentAdaDialog);
      }

      if (interactionFlag == Interaction::RailDialog) {
         textures->dialogBox.render(window, 50, 50);
         textures->adaRailDialog[currentRailDialog - 1].render(window, 75, 75);
      }

      // Render the rail cipher if it is its turn
      if (interactionFlag == Interaction::RailCipher) {
         textures->AdaRailCipherScreen.render(window, 0, 0);
         for (int i = 0; i < 30; i++) {
            rail[i].render(window, textures);
         }
         for (int i = 0; i < railAlphabet.size(); i++) {
            railAlphabet[i].render(window, textures);
         }
         if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
            interactionFlag = Interaction::RailDialog;
         }
      }

      // Render Casar
      if (interactionFlag == Interaction::CaesarCipher) {
         textures->ada_screen.render(window, 0, 0);
         textures->start_state.render(window, 0, 0);
         for (int i = 0; i < 7; ++i)
         {
            caesar[i].render(window, textures);
         }

         if (caesar[2].isPressed()) {
            textures->state_4.render(window, 0, 0);
         }
         if (caesar[3].isPressed()) {
            textures->state_5.render(window, 0, 0);
         }

         if (caesar[5].isPressed()) {
            textures->state_7.render(window, 0, 0);
         }

         if (caesar[1].isPressed()) {
            bool clean = true;
            if (caesar[5].isPressed()) {
               textures->state_3.render(window, 0, 0);
               textures->state_7.render(window, 0, 0);
               clean = false;
            }
            if (caesar[3].isPressed()) {
               textures->state_3.render(window, 0, 0);
               textures->state_5.render(window, 0, 0);
               clean = false;
            }
            if (clean == true) {
               textures->state_3.render(window, 0, 0);
            }
         }

         if (caesar[4].isPressed()) {
            textures->state_6.render(window, 0, 0);
         }
      }

      //printf("pos X: %d, pos y: %d\n", character.getPosX(), character.getPosY());
      //printf("current inteaction = %d\n", (int)interactionFlag);

      // Update screen
      SDL_RenderPresent(window->renderer);

      // Sleep for a short while to add pixel-styled movement
      SDL_Delay(50);
   }
}

void renderHome(Window* window, Textures* textures, SDL_Rect* camera)
{
   // Render the home in the middle of a screen and reset the camera
   camera->x = 0; camera->y = 0;
   textures->home.render(window, CAMERA_WIDTH / 2 - textures->home.getWidth() / 2,
      CAMERA_HEIGHT / 2 - textures->home.getHeight() / 2);
}

void renderWorld(Window* window, Textures* textures, Character* character, Ada* ada, SDL_Rect* camera, std::vector<Npc> npcs,
   int* currentAnimation)
{
   // Render background clipped to the camera screen
   textures->worldmap.render(window, 0, 0, camera);
   character->render(window, textures, camera->x, camera->y, *currentAnimation);
   // Render Ada if active
   if (ada->getAdaActive()) {
      ada->render(window, textures, camera->x, camera->y, *currentAnimation);
   }
   textures->objects.render(window, 0, 0, camera);

   // Render all the NPCs
   for (auto npc : npcs) {
      npc.render(window, textures, camera->x, camera->y);
   }

   // Center the camera with the focus on the character and keep it in bounds of the map
   cameraFocus(camera, character);
}

void cameraFocus(SDL_Rect* camera, Character* character)
{
   // Center the camera over the character 
   camera->x = (character->getPosX() + TILE_SIZE / 2) - CAMERA_WIDTH / 2;
   camera->y = (character->getPosY() + TILE_SIZE / 2) - CAMERA_HEIGHT / 2;
   
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
   int currentFrame = (int) character->getCurrentDirection();
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

bool checkCollision(SDL_Rect rect1, const SDL_Rect rect2)
{
   // Find the edges of player:
   int rect1Left = rect1.x;
   int rect1Right = rect1.x + rect1.w;
   int rect1Top = rect1.y;
   int rect1Bottom = rect1.y + rect1.h;

   // Find the edges of an collision object:
   int rect2Left = rect2.x;
   int rect2Right = rect2.x + rect2.w;
   int rect2Top = rect2.y;
   int rect2Bottom = rect2.y + rect2.h;

   // Does player's right side touch with collider's left side?
   if (rect1Right < rect2Left)
      return false; // no collision
   if (rect1Left > rect2Right)
      return false;
   if (rect1Top > rect2Bottom)
      return false;
   if (rect1Bottom < rect2Top)
      return false;

   return true; // collision found!!
}

void checkForObjectsCollision(Character *character, Ada* ada, std::vector<Obstacles> obstacles, std::vector<Npc> npcs,
   int playerPositionX, int playerPositionY, int adaPositionX, int adaPositionY)
{
   SDL_Rect playerLocation = { character->getPosX() , character->getPosY(), TILE_SIZE, TILE_SIZE };

   // Check collisions with NPC all the NPCs
   for (auto npc : npcs) {
      if (checkCollision(playerLocation, npc.getLocation())) {
         character->setPlayerPosX(playerPositionX);
         character->setPlayerPosY(playerPositionY);
         ada->setAdaPosX(adaPositionX);
         ada->setAdaPosY(adaPositionY);
      }
   }
   // Run through all the obstacle rects and check for collision
   // If collision found return sprite back to the position before the movement
   for (const auto obstacle : obstacles) {
      if (checkCollision(playerLocation, obstacle.pos)) {
         character->setPlayerPosX(playerPositionX);
         character->setPlayerPosY(playerPositionY);
         ada->setAdaPosX(adaPositionX);
         ada->setAdaPosY(adaPositionY);
      }
   }
}

Interaction checkForInteraction(Character *character, Ada *ada, std::vector<Npc> npcs)
{
   // Check for the first interaction with Ada in the home location; if found set ada active
   if ((character->getCurrentLocation() == Location::Home) && (ada->getAdaActive() == false) &&
      ((character->getPosX() == 672 && character->getPosY() == 360) || (character->getPosX() == 704 && character->getPosY() == 392))) {
      // return the correct interaction
      return Interaction::AdaInitialization;
   }

   // Check for interaction for rail puzzle in the left-bottom 'dungeon'
   if ((character->getCurrentLocation() == Location::World) && (ada->getAdaActive() == true) &&
      (character->getCurrentDirection() == Direction::Up) &&
      ((character->getPosX() == 3360 && character->getPosY() == 1952) || 
      (character->getPosX() == 3328 && character->getPosY() == 1952))) {
      // return the correct interaction
      return Interaction::RailDialog;
   }
   // I have no idea why he locations are supposed to be like this :D I suppose 2nd and 4th if-statement make sense
   // But the 1st and 3rd are trial-and-error :D
   for (auto npc : npcs) {
      if ((npc.getLocation().x - 64 == character->getPosX()) && (npc.getLocation().y == character->getPosY() + 32)
         && (character->getCurrentDirection() == Direction::Right)) {
         return Interaction::Npc;
      }
      if ((npc.getLocation().x - 32 == character->getPosX()) && (npc.getLocation().y == character->getPosY())
         && (character->getCurrentDirection() == Direction::Up)) {
         return Interaction::Npc;
      }
      if ((npc.getLocation().y - 64 == character->getPosY()) && (npc.getLocation().x == character->getPosX() + 32)
         && (character->getCurrentDirection() == Direction::Down)) {
         return Interaction::Npc;
      }
      if ((npc.getLocation().y - 32 == character->getPosY()) && (npc.getLocation().x == character->getPosX())
         && (character->getCurrentDirection() == Direction::Left)) {
         return Interaction::Npc;
      }
   }

   return Interaction::None;
}

void StartAdaInitializationEvent(Window* window, Textures* textures, Ada* ada, int currentAdaDialog)
{
   textures->dialogBox.render(window, 50, 50);
   textures->adaInitializationDialog[currentAdaDialog - 1].render(window, 75, 75);
}