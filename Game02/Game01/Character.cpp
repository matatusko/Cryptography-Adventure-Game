#include "Main.h"
#include "Character.h"

Character::Character()
{
   // Initialize the begining position of our character
   posX = 1984;
   posY = 1856;

   // Initialize the current velocity of the character for movement
   velX = 0;
   velY = 0;

   // Initialize sprite animation and set the current clip to 0
   setSpriteClips();
   currentClip = 0;
   characterMoving = false;
}

void Character::handleEvents(SDL_Event &e)
{
   // Key pressed
   if (e.type == SDL_KEYDOWN/* && e.key.repeat == 0 */) {
      characterMoving = true;
      // Move the character according to the key pressed
      switch (e.key.keysym.sym) {
         case SDLK_UP:
            posY -= CHARACTER_VELOCITY;
            currentClip = 8;
            break;
         case SDLK_DOWN:
            posY += CHARACTER_VELOCITY;
            currentClip = 0;
            break;
         case SDLK_LEFT:
            posX -= CHARACTER_VELOCITY;
            currentClip = 12;
            break;
         case SDLK_RIGHT:
            posX += CHARACTER_VELOCITY;
            currentClip = 4;
            break;
      }
   } 
   // Key released
   if (e.type == SDL_KEYUP/* && e.key.repeat == 0 */) {
      characterMoving = false;
      // Reset the character's velocity by adjusting it
      switch (e.key.keysym.sym) {
         case SDLK_UP:
//            posY += CHARACTER_VELOCITY;
            currentClip = 8;
            break;
         case SDLK_DOWN:
//            posY -= CHARACTER_VELOCITY;
            currentClip = 0;
            break;
         case SDLK_LEFT:
//            posX += CHARACTER_VELOCITY;
            currentClip = 12;
            break;
         case SDLK_RIGHT:
//            posX -= CHARACTER_VELOCITY;
            currentClip = 4;
            break;
      } 
   } 
}

void Character::move()
{
   // Move the dot left or right and take care of an event when the character goes out of screen
   posX += velX;
   if ((posX < 0) || (posX + CHARACTER_WIDTH > MAP_WIDTH)) {
      posX -= velX;
   }
   // Do the same for up and down
   posY += velY;
   if ((posY < 0) || (posY + CHARACTER_HEIGHT > MAP_HEIGHT)) {
      posY -= velY;
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

int Character::getCurrentClip()
{
   return currentClip;
}

bool Character::getCharacterMoving()
{
   return characterMoving;
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
         spriteClips[current_index].w = CHARACTER_WIDTH;
         spriteClips[current_index].h = CHARACTER_HEIGHT;
         next_x += CHARACTER_WIDTH;
         current_index++;
      }
      next_x = 0;
      next_y += CHARACTER_HEIGHT;
   }
}