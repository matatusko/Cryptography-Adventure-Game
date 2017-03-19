#include "Main.h"
#include "Rail.h"

Rail::Rail(int x, int y, int sprite)
{
   position.x = x;
   position.y = y;
   currentSprite = sprite;
   lastSprite = sprite;
   coloredSprite = sprite + 30;
}

void Rail::render(Window* window, Textures* textures)
{
   textures->railCipher.render(window, position.x, position.y, &(textures->railButtons[currentSprite]));
}

void Rail::handleEvents(SDL_Event* e)
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
      else if (x > position.x + 66)
      {
         inside = false;
      }
      //Mouse above the button
      else if (y < position.y)
      {
         inside = false;
      }
      //Mouse below the button
      else if (y > position.y + 66)
      {
         inside = false;
      }

      //Mouse is outside button
      if (!inside)
      {
         currentSprite = lastSprite;
      }

      //Mouse is inside button
      else
      {
         //Set mouse over sprite
         switch (e->type)
         {
         case SDL_MOUSEBUTTONDOWN:
            currentSprite = coloredSprite;
            lastSprite = coloredSprite;
            break;
         case SDL_MOUSEMOTION:
            currentSprite = coloredSprite;
            break;
         }
      }
   }
}