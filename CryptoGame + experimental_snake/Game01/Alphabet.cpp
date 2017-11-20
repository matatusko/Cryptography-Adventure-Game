#include "Main.h"
#include "Alphabet.h"

#include "Main.h"
#include "Rail.h"

Alphabet::Alphabet(int x, int y, int sprite)
{
   position.x = x;
   position.y = y;
   currentSprite = sprite;
}

int Alphabet::getCurrentSprite() {
   return currentSprite;
}

void Alphabet::setCurrentSprite(int x) {
   currentSprite = x;
}

void Alphabet::render(Window* window, Textures* textures)
{
   textures->alphabet.render(window, position.x, position.y, &(textures->alphabetLetters[currentSprite]));
}

void Alphabet::handleEvents(SDL_Event* e)
{
   //If mouse event happened
   if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
   {
      //Get mouse position
      int x, y;
      SDL_GetMouseState(&x, &y);

      //Check if mouse is in button
      bool inside = true;

      //Mouse is left of the button
      if (x < position.x)
      {
         inside = false;
      }
      //Mouse is right of the button
      else if (x > position.x + 54)
      {
         inside = false;
      }
      //Mouse above the button
      else if (y < position.y)
      {
         inside = false;
      }
      //Mouse below the button
      else if (y > position.y + 54)
      {
         inside = false;
      }

      //Mouse is inside button
      else
      {
         if (e->type == SDL_MOUSEBUTTONDOWN && e->key.repeat == 0)
         switch (e->button.button) {
         case SDL_BUTTON_LEFT:
               currentSprite += 1;
               if (currentSprite > 25) {
                  currentSprite = 0;
               }
               break;
         case SDL_BUTTON_RIGHT:
               currentSprite = currentSprite - 1;
               if (currentSprite < 0) {
                  currentSprite = 25;
               }
               break;
         }
      }
   }
}