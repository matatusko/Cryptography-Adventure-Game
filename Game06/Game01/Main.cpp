#include "Main.h"

int main(int argc, char* argv[])
{
   // Initialize all the structures, variables and main classes
   Window window;
   Textures textures;
   Puzzles puzzles;
   GameObjects gameObjects;

   // Set up the window class, including the renderer and all the SDL functions
   window.initialize();
   srand(time(NULL));

   // Load all the necessary media to run the game and place them into corresponding textures. 
   // If failed print an error and shut down the game.
   if (!loadMedia(&textures, &window)) {
      std::cout << "Failed loading media. Terminating program." << std::endl;
   }
   else {
      gameLoop(&textures, &window, &puzzles, &gameObjects);
   }

   // Close window, renderer and all the other SDL stuff
   window.cleanup();
   return 0;
}

void gameLoop(Textures* textures, Window* window, Puzzles* puzzles, GameObjects* gameObjects)
{
   // Initialize all the objects and puzzles, including cutting the spitesheets, setting up the NPCs,
   // preparing the puzzles, getting the camera set up etc.
   // If any of the variables failed to initialize, print the error message and shut down the game
   if (!initializeVariables(textures, window, puzzles, gameObjects)) {
      std::cout << "Failed initializing all the variables. Terminating program." << std::endl;
      return;
   }

   // Variables initialized correctly - set the game loop flag to true, get the SDL_Event and enter the main game loop
   bool gameRunning = true;
   SDL_Event e;

   // Start the game loop
   while (gameRunning) {

      // Get the old position of the character before the movement so we can return it to that particular position
      // in case of collision. Also, find a frame to animate a character
      getPreMovementVariables(gameObjects);

      // Handle the main game events on queue
      while (SDL_PollEvent(&e) != 0) {
         // Check for quit signal
         if (e.type == SDL_QUIT) {
            gameRunning = false;
         }

         handleInteractionInput(e, gameObjects);
         handlePuzzleEvents(e, gameObjects, puzzles);
         handleTheMovementAndCollisions(e, textures, gameObjects);
         // automaticCollisions(e, gameObjects);
      }

      renderEverything(window, textures, gameObjects, puzzles, e);

      // FOR DEBUGGING
      // printf("pos X: %d, pos y: %d\n", character.getPosX(), character.getPosY());
      // printf("current inteaction = %d\n", (int)interactionFlag);

      // Sleep for a short while to add pixel-styled movement
      SDL_Delay(50);
   }
}



// LOOP SETTING VARIABLES

void getPreMovementVariables(GameObjects* gameObjects)
{
   // Get the current player and ada's position so if the collision happens they can return to the
   // position they were before the movement
   gameObjects->playerPositionX = gameObjects->character.getPosX();
   gameObjects->playerPositionY = gameObjects->character.getPosY();
   gameObjects->adaPositionX = gameObjects->ada.getAdaPosX();
   gameObjects->adaPositionY = gameObjects->ada.getAdaPosY();

   // Select the proper animation clip to render
   gameObjects->currentAnimation = animateCharacter(gameObjects);
}

int animateCharacter(GameObjects* gameObjects) {

   static int frameChange = 0;
   int currentFrame = (int)gameObjects->character.getCurrentDirection();
   // Checks if the character is moving, and if it is increases the current movement state by +1
   // up to 4 times, when it returns back to the original when the key is pressed up
   if (gameObjects->character.getCharacterMoving()) {
      frameChange++;
      if (frameChange >= 8) {
         frameChange = 0;
      }
      currentFrame += frameChange / 2;
   }

   return currentFrame;
}

void cameraFocus(GameObjects* gameObjects)
{
   // Center the camera over the character 
   gameObjects->camera.x = (gameObjects->character.getPosX() + TILE_SIZE / 2) - CAMERA_WIDTH / 2;
   gameObjects->camera.y = (gameObjects->character.getPosY() + TILE_SIZE / 2) - CAMERA_HEIGHT / 2;
   
   // Prevent the camera from leaving the map screen
   if (gameObjects->camera.x < 0) {
      gameObjects->camera.x = 0;
   }
   if (gameObjects->camera.y < 0) {
      gameObjects->camera.y = 0;
   }
   if (gameObjects->camera.x > MAP_WIDTH - gameObjects->camera.w) {
      gameObjects->camera.x = MAP_WIDTH - gameObjects->camera.w;
   }
   if (gameObjects->camera.y > MAP_HEIGHT - gameObjects->camera.h) {
      gameObjects->camera.y = MAP_HEIGHT - gameObjects->camera.h;
   }
}


// COLLISIONS, EVENTS AND MOVEMENT

bool mainCollisionFunction(SDL_Rect rect1, const SDL_Rect rect2)
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

void checkForCollisionsWithObstacles(GameObjects* gameObjects)
{
   SDL_Rect playerLocation = { gameObjects->character.getPosX() , gameObjects->character.getPosY(), TILE_SIZE, TILE_SIZE };

   // Check collisions with NPC all the NPCs
   for (auto npc : gameObjects->npcs) {
      if (mainCollisionFunction(playerLocation, npc.getLocation())) {
         gameObjects->character.setPlayerPosX(gameObjects->playerPositionX);
         gameObjects->character.setPlayerPosY(gameObjects->playerPositionY);
         gameObjects->ada.setAdaPosX(gameObjects->adaPositionX);
         gameObjects->ada.setAdaPosY(gameObjects->adaPositionY);
      }
   }
   // Run through all the obstacle rects and check for collision
   // If collision found return sprite back to the position before the movement
   for (const auto obstacle : gameObjects->obstacles) {
      if (mainCollisionFunction(playerLocation, obstacle.pos)) {
         gameObjects->character.setPlayerPosX(gameObjects->playerPositionX);
         gameObjects->character.setPlayerPosY(gameObjects->playerPositionY);
         gameObjects->ada.setAdaPosX(gameObjects->adaPositionX);
         gameObjects->ada.setAdaPosY(gameObjects->adaPositionY);
      }
   }
}

Interaction checkForInteraction(GameObjects* gameObjects)
{
   // Check for the first interaction with Ada in the home location; if found set ada active
   if ((gameObjects->character.getCurrentLocation() == Location::Home) && (gameObjects->ada.getAdaActive() == false) &&
      ((gameObjects->character.getPosX() == 672 && gameObjects->character.getPosY() == 360) || (gameObjects->character.getPosX() == 704 && gameObjects->character.getPosY() == 392))) {
      // return the correct interaction
      return Interaction::AdaInitialization;
   }

   // Check for interaction for rail puzzle in the left-bottom 'dungeon'
   if ((gameObjects->character.getCurrentLocation() == Location::World) && (gameObjects->ada.getAdaActive() == true) &&
      (gameObjects->character.getCurrentDirection() == Direction::Up) &&
      ((gameObjects->character.getPosX() == 3360 && gameObjects->character.getPosY() == 1952) || 
      (gameObjects->character.getPosX() == 3328 && gameObjects->character.getPosY() == 1952))) {
      // return the correct interaction
      return Interaction::RailDialog;
   }
   // I have no idea why he locations are supposed to be like this :D I suppose 2nd and 4th if-statement make sense
   // But the 1st and 3rd are trial-and-error :D
   for (auto npc : gameObjects->npcs) {
      if ((npc.getLocation().x - 64 == gameObjects->character.getPosX()) && (npc.getLocation().y == gameObjects->character.getPosY() + 32)
         && (gameObjects->character.getCurrentDirection() == Direction::Right)) {
         return Interaction::Npc;
      }
      if ((npc.getLocation().x - 32 == gameObjects->character.getPosX()) && (npc.getLocation().y == gameObjects->character.getPosY())
         && (gameObjects->character.getCurrentDirection() == Direction::Up)) {
         return Interaction::Npc;
      }
      if ((npc.getLocation().y - 64 == gameObjects->character.getPosY()) && (npc.getLocation().x == gameObjects->character.getPosX() + 32)
         && (gameObjects->character.getCurrentDirection() == Direction::Down)) {
         return Interaction::Npc;
      }
      if ((npc.getLocation().y - 32 == gameObjects->character.getPosY()) && (npc.getLocation().x == gameObjects->character.getPosX())
         && (gameObjects->character.getCurrentDirection() == Direction::Left)) {
         return Interaction::Npc;
      }
   }

   return Interaction::None;
}

void handleInteractionInput(SDL_Event &e, GameObjects* gameObjects)
{
   // Check for space when there is no interaction goin on at all and sets the number to print random dialog for NPC
   if (e.type == SDL_KEYDOWN &&
      e.key.keysym.sym == SDLK_SPACE &&
      gameObjects->interactionFlag == Interaction::None) {
      gameObjects->interactionFlag = checkForInteraction(gameObjects);
      gameObjects->currentNPCdialog = rand() % 6;
   }
   // When the AdaInitialization event is running, checks for space to increase the current dialog being shown
   // to the player
   if (e.type == SDL_KEYDOWN &&
      e.key.keysym.sym == SDLK_SPACE &&
      gameObjects->interactionFlag == Interaction::AdaInitialization
      && e.key.repeat == 0) {
      gameObjects->adaInitializationDialog++;
      // Dialog over, set Ada to active so she follows around and reset interaction flag to none
      if (gameObjects->adaInitializationDialog > 3) {
         gameObjects->ada.setAdaActive(true);
         gameObjects->interactionFlag = Interaction::None;
      }
      // Dialog in the middle, run the Caesar Cipher
      if (gameObjects->adaInitializationDialog == 2) {
         gameObjects->interactionFlag = Interaction::CaesarCipher;
      }
   }
   // Run the dialog for the Rail Cipther event
   if (e.type == SDL_KEYDOWN &&
      e.key.keysym.sym == SDLK_SPACE &&
      gameObjects->interactionFlag == Interaction::RailDialog
      && e.key.repeat == 0) {
      gameObjects->adaCurrentRailDialog++;
      // Change the interaction to Rail Cipher when the right place in dialog occurs 
      if (gameObjects->adaCurrentRailDialog == 5) {
         gameObjects->interactionFlag = Interaction::RailCipher;
      }
      // Puzzles were solved and rail event is over
      if (gameObjects->adaCurrentRailDialog >= 8) {
         gameObjects->interactionFlag = Interaction::None;
      }
   }
}

void handlePuzzleEvents(SDL_Event &e, GameObjects* gameObjects, Puzzles* puzzles)
{
   // Handle the mouse movement for rail cipher
   if (gameObjects->interactionFlag == Interaction::RailCipher) {
      for (int i = 0; i < 60; i++) {
         puzzles->rail[i].handleEvents(&e);
      }
      for (int i = 0; i < puzzles->railAlphabet.size(); i++) {
         puzzles->railAlphabet[i].handleEvents(&e);
      }
   }
   // Handle the mouse movement for Caesar
   if (gameObjects->interactionFlag == Interaction::CaesarCipher) {
      for (int i = 0; i < 7; i++) {
         puzzles->caesar[i].handleEvent(&e);
      }
   }
}

void handleTheMovementAndCollisions(SDL_Event& e, Textures* textures, GameObjects* gameObjects)
{
   // Handle the character movement and wall collisions
   gameObjects->character.handleMovement(e);
   gameObjects->character.CheckForWallCollisions(textures);

   // Move Ada right after the character and don't move it if the character is not moving
   // so she doesn't enter onto the character when he stops.
   // Ada only moves once she has been activated by character
   if (gameObjects->character.getCharacterMoving() && gameObjects->ada.getAdaActive()) {
      gameObjects->ada.setAdaPosX(gameObjects->playerPositionX);
      gameObjects->ada.setAdaPosY(gameObjects->playerPositionY);
   }

   // Check for collisions and if those happen return character right to their original positions
   // before collision happened
   if (gameObjects->character.getCurrentLocation() == Location::World) {
      checkForCollisionsWithObstacles(gameObjects);
   }
}


// RENDERING FUNCTION

void renderEverything(Window* window, Textures* textures, GameObjects* gameObjects, Puzzles* puzzles, SDL_Event &e)
{
   // Clear screen
   SDL_RenderClear(window->renderer);

   // Function name says it all, more info in separate functions
   renderMainGameScreen(window, textures, gameObjects, puzzles);
   renderNPCDialogs(window, textures, gameObjects);
   renderAdaDialogs(window, textures, gameObjects);
   renderRailCipher(window, textures, gameObjects, puzzles, e);
   renderCaesarCipher(window, textures, gameObjects, puzzles);

   // Update screen
   SDL_RenderPresent(window->renderer);
}

void renderMainGameScreen(Window* window, Textures* textures, GameObjects* gameObjects, Puzzles* puzzles)
{
   // Render Home
   if (gameObjects->character.getCurrentLocation() == Location::Home) {
      renderHome(window, textures, gameObjects);
      // Render character
      gameObjects->character.render(window, textures, gameObjects->camera.x, gameObjects->camera.y, gameObjects->currentAnimation);
      gameObjects->ada.render(window, textures, gameObjects->camera.x, gameObjects->camera.y, gameObjects->currentAnimation);
   }
   // Else render the whole world
   else if (gameObjects->character.getCurrentLocation() == Location::World) {
      renderWorld(window, textures, gameObjects);
   }
}

void renderHome(Window* window, Textures* textures, GameObjects* gameObjects)
{
   // Render the home in the middle of a screen and reset the camera
   gameObjects->camera.x = 0; gameObjects->camera.y = 0;
   textures->home.render(window, CAMERA_WIDTH / 2 - textures->home.getWidth() / 2,
      CAMERA_HEIGHT / 2 - textures->home.getHeight() / 2);
}

void renderWorld(Window* window, Textures* textures, GameObjects* gameObjects)
{
   // Render background map clipped to the camera screen
   textures->worldmap.render(window, 0, 0, &(gameObjects->camera));

   // Render the character
   gameObjects->character.render(window, textures, gameObjects->camera.x, gameObjects->camera.y, gameObjects->currentAnimation);
   // Render Ada if active
   if (gameObjects->ada.getAdaActive()) {
      gameObjects->ada.render(window, textures, gameObjects->camera.x, gameObjects->camera.y, gameObjects->currentAnimation);
   }

   // Render the textures with object last so we get a nice transparency effect
   textures->objects.render(window, 0, 0, &(gameObjects->camera));

   // Render all the NPCs
   for (auto npc : gameObjects->npcs) {
      npc.render(window, textures, gameObjects->camera.x, gameObjects->camera.y);
   }

   // Center the camera with the focus on the character and keep it in bounds of the map
   cameraFocus(gameObjects);
}

void renderNPCDialogs(Window* window, Textures* textures, GameObjects* gameObjects)
{
   // No interaction when character starts moving hence will kill the dialog window
   if (gameObjects->character.getCharacterMoving()) {
      gameObjects->interactionFlag = Interaction::None;
   }

   // Print the npc interaction dialog if found
   if (gameObjects->interactionFlag == Interaction::Npc) {
      textures->dialogBox.render(window, 50, 50);
      textures->npcDialogText[gameObjects->currentNPCdialog].render(window, 75, 75);
   }
}

void renderAdaDialogs(Window* window, Textures* textures, GameObjects* gameObjects)
{
   // Start the Ada initialization events
   if (gameObjects->interactionFlag == Interaction::AdaInitialization) {
      textures->dialogBox.render(window, 50, 50);
      textures->adaInitializationDialog[gameObjects->adaInitializationDialog - 1].render(window, 75, 75);
   }

   // Start the rail cipher event
   if (gameObjects->interactionFlag == Interaction::RailDialog) {
      textures->dialogBox.render(window, 50, 50);
      textures->adaRailDialog[gameObjects->adaCurrentRailDialog - 1].render(window, 75, 75);
   }
}

void renderRailCipher(Window* window, Textures* textures, GameObjects* gameObjects, Puzzles* puzzles, SDL_Event &e)
{
   // Render the rail cipher if it is its turn
   if (gameObjects->interactionFlag == Interaction::RailCipher) {
      // Get the main console on-screen
      textures->AdaRailCipherScreen.render(window, 0, 0);
      // render each rail buttons along with their events
      for (int i = 0; i < 30; i++) {
         puzzles->rail[i].render(window, textures);
      }
      // render each Alphabet letter for the user input
      // TODO: solved function
      for (int i = 0; i < puzzles->railAlphabet.size(); i++) {
         puzzles->railAlphabet[i].render(window, textures);
      }
      // Close the screen if esc clicked
      if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
         gameObjects->interactionFlag = Interaction::RailDialog;
      }
   }
}

void renderCaesarCipher(Window* window, Textures* textures, GameObjects* gameObjects, Puzzles* puzzles)
{
   // Render Casar
   if (gameObjects->interactionFlag == Interaction::CaesarCipher) {
      textures->ada_screen.render(window, 0, 0);
      textures->start_state.render(window, 0, 0);
      for (int i = 0; i < 7; ++i)
      {
         puzzles->caesar[i].render(window, textures);
      }

      if (puzzles->caesar[2].isPressed()) {
         textures->state_4.render(window, 0, 0);
      }
      if (puzzles->caesar[3].isPressed()) {
         textures->state_5.render(window, 0, 0);
      }

      if (puzzles->caesar[5].isPressed()) {
         textures->state_7.render(window, 0, 0);
      }

      if (puzzles->caesar[1].isPressed()) {
         bool clean = true;
         if (puzzles->caesar[5].isPressed()) {
            textures->state_3.render(window, 0, 0);
            textures->state_7.render(window, 0, 0);
            clean = false;
         }
         if (puzzles->caesar[3].isPressed()) {
            textures->state_3.render(window, 0, 0);
            textures->state_5.render(window, 0, 0);
            clean = false;
         }
         if (clean == true) {
            textures->state_3.render(window, 0, 0);
         }
      }

      if (puzzles->caesar[4].isPressed()) {
         textures->state_6.render(window, 0, 0);
      }
   }
}