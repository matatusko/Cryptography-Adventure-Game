#include "Main.h"
#include "Morse.h"


bool Morse::isPressed() {
   return pressed;
}

void Morse::resetPress() {
   pressed = false;
}

Morse::Morse(int x, int y, int current_sprite)
{
   mPosition.x = x;
   mPosition.y = y;

   pressed = false;

   mCurrentSprite = 0;
   mLastSprite = 0;
   hoversprite = 1;

}

void Morse::handleEvent(SDL_Event* e)
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
      if (x < mPosition.x)
      {
         inside = false;
      }
      //Mouse is right of the button
      else if (x > mPosition.x + 100)
      {
         inside = false;
      }
      //Mouse above the button
      else if (y < mPosition.y)
      {
         inside = false;
      }
      //Mouse below the button
      else if (y > mPosition.y + 100)
      {
         inside = false;
      }

      //Mouse is outside button
      if (!inside)
      {
         mCurrentSprite = mLastSprite;
      }
      //Mouse is inside button
      else
      {
         //Set mouse over sprite
         switch (e->type)
         {
         case SDL_MOUSEMOTION:
            mCurrentSprite = hoversprite;
            // std::cout << hoversprite << std::endl;
            break;

         case SDL_MOUSEBUTTONDOWN:
            pressed = true;
            break;
         }
      }
   }
}

void Morse::render(Window* window, Textures* textures)
{
   //Show current button sprite
   textures->morseButtonSpritesheet.render(window, mPosition.x, mPosition.y, &(textures->morseButton[mCurrentSprite]));
}