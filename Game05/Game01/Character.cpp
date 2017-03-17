#include "Main.h"
#include "Character.h"

Character::Character()
{
   // Initialize the begining position of our character
   posX = CAMERA_WIDTH / 2;
   posY = CAMERA_HEIGHT / 2;

   // Set the initial location to home
   currentLoc = Location::Home;
   currentDirection = Direction::Down;

   // Initialize sprite animation and set the current clip to 0
   setSpriteClips();
   characterMoving = false;
}

void Character::handleMovement(SDL_Event &e)
{
   // Key pressed
   if (e.type == SDL_KEYDOWN && e.key.keysym.sym != SDLK_SPACE) {
      characterMoving = true;
      // Move the character according to the key pressed
      switch (e.key.keysym.sym) {
         case SDLK_UP:
            posY -= TILE_SIZE;
            currentDirection = Direction::Up;
            break;
         case SDLK_DOWN:
            posY += TILE_SIZE;
            currentDirection = Direction::Down;
            break;
         case SDLK_LEFT:
            posX -= TILE_SIZE;
            currentDirection = Direction::Left;
            break;
         case SDLK_RIGHT:
            posX += TILE_SIZE;
            currentDirection = Direction::Right;
            break;
      }
   } 
   // Key released
   if (e.type == SDL_KEYUP) {
      characterMoving = false;
      // Reset the character's velocity by adjusting it
      switch (e.key.keysym.sym) {
         case SDLK_UP:
            currentDirection = Direction::Up;
            break;
         case SDLK_DOWN:
            currentDirection = Direction::Down;
            break;
         case SDLK_LEFT:
            currentDirection = Direction::Left;
            break;
         case SDLK_RIGHT:
            currentDirection = Direction::Right;
            break;
      } 
   } 
}

void Character::CheckForWallCollisions(Textures* textures)
{
   if (currentLoc == Location::World) {
      // Check if the character is trying to go out of the world map or is trying to enter another area
      if ((posX == 1984 || posX == 1952) && (posY == 1792)) {
         currentLoc = Location::Home;
         posX = 640;
         posY = 424;
      }
      if (posX < 128) {
         posX += TILE_SIZE;
      }
      if (posX + TILE_SIZE > MAP_WIDTH - 128) {
         posX -= TILE_SIZE;
      }
      if (posY < 0) {
         posY += TILE_SIZE;
      }
      if (posY + TILE_SIZE > MAP_HEIGHT - 32) {
         posY -= TILE_SIZE;
      }
      
   }

   if (currentLoc == Location::Home) {
      // Check if the character is touching the walls in the house or the door
      if (posY >= CAMERA_HEIGHT / 2 + textures->home.getHeight() / 2 - 32) {
         currentLoc = Location::World;
         posX = 2016;
         posY = 1856;
      }
      if (posX <= CAMERA_WIDTH / 2 - textures->home.getWidth() / 2) {
         posX += TILE_SIZE;
      }
      if (posX + TILE_SIZE > CAMERA_WIDTH / 2 + textures->home.getWidth() / 2) {
         posX -= TILE_SIZE;
      }
      if (posY <= CAMERA_HEIGHT / 2 - textures->home.getHeight() / 2 + 32 ) {
         posY += TILE_SIZE;
      }
      // Leave the space so the character can pass through the door
      if (((posY + TILE_SIZE > CAMERA_HEIGHT / 2 + textures->home.getHeight() / 2 - 64) &&
               (posX <= CAMERA_WIDTH / 2 - textures->home.getWidth() / 2 + 224)) ||
               ((posY + TILE_SIZE > CAMERA_HEIGHT / 2 + textures->home.getHeight() / 2 - 64) &&
               (posX >= CAMERA_WIDTH / 2 - textures->home.getWidth() / 2 + 256))) {
         posY -= TILE_SIZE;
      }
   } 
}

void Character::render(Window* window, Textures* textures, int camX, int camY, int animation)
{
   textures->character.render(window, posX - camX, posY - camY, &spriteClips[animation]);
}

int Character::getPosX()
{
   return posX;
}

int Character::getPosY()
{
   return posY;
}

Direction Character::getCurrentDirection()
{
   return currentDirection;
}

bool Character::getCharacterMoving()
{
   return characterMoving;
}

Location Character::getCurrentLocation()
{
   return currentLoc;
}

void Character::setPlayerPosX(int positionXToSet)
{
   posX = positionXToSet;
}

void Character::setPlayerPosY(int positionYToSet)
{
   posY = positionYToSet;
}

void Character::setSpriteClips()
{
   // Here I'm cutting the character sprite sheet into 16 separate sprites
   // Each sprite is 32x32 so I'm looping through each column, selecting sprites one by one
   // and adding them to a proper position in the array. Next I'm moving to rows and 
   // doing the same thing.
   int next_x = 0, next_y = 0, current_index = 0;
   for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
         spriteClips[current_index].x = next_x;
         spriteClips[current_index].y = next_y;
         spriteClips[current_index].w = TILE_SIZE;
         spriteClips[current_index].h = TILE_SIZE;
         next_x += TILE_SIZE;
         current_index++;
      }
      next_x = 0;
      next_y += TILE_SIZE;
   }
}