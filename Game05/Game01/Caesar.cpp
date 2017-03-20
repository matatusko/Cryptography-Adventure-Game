#include "Main.h"
#include "Caesar.h"

bool Caesar::isPressed() {
   return pressed;
}

void Caesar::resetPress() {
   pressed = false;
}

Caesar::Caesar(int x, int y, int current_sprite)
{
   mPosition.x = x;
   mPosition.y = y;

   pressed = false;

   mCurrentSprite = current_sprite;
   mLastSprite = current_sprite;
   hoversprite = current_sprite + 7;
   presssprite = current_sprite + 14;
}

void Caesar::handleEvent(SDL_Event* e)
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
      else if (x > mPosition.x + 88)
      {
         inside = false;
      }
      //Mouse above the button
      else if (y < mPosition.y)
      {
         inside = false;
      }
      //Mouse below the button
      else if (y > mPosition.y + 88)
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
            break;

         case SDL_MOUSEBUTTONDOWN:
            mCurrentSprite = presssprite;
            mLastSprite = presssprite;
            pressed = true;
            break;

            // case SDL_MOUSEBUTTONUP:
            // mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
            // break;
         }
      }
   }
}

void Caesar::render(Window* window, Textures* textures)
{
   //Show current button sprite
   textures->caesarButtonsSpritesheet.render(window, mPosition.x, mPosition.y, &(textures->caesarButtons[mCurrentSprite]));
}