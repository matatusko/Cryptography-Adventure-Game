#include "Main.h"
#include "AdaInterfaceButtons.h"

AdaInterfaceButtons::AdaInterfaceButtons(int x, int y, int button, CurrentHelp buttonType)
{
   position.x = x;
   position.y = y;
   currentSprite = button;
   lastSprite = button;
   coloredSprite = button + 1;
   type = buttonType;
}

void AdaInterfaceButtons::render(Window* window, Textures* textures)
{
   textures->interfaceButtonsSpritesheet.render(window, position.x, position.y, 
      &(textures->interfaceButtons[currentSprite]));
}

void AdaInterfaceButtons::handleEvents(SDL_Event* e, Textures* textures)
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
      else if (x > position.x + 133)
      {
         inside = false;
      }
      //Mouse above the button
      else if (y < position.y)
      {
         inside = false;
      }
      //Mouse below the button
      else if (y > position.y + 27)
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
            if (type == CurrentHelp::AdaHelpWindow) {
               textures->currentHelp = CurrentHelp::AdaHelpWindow;
            }
            else if (type == CurrentHelp::CaesarExplanation) {
               textures->currentHelp = CurrentHelp::CaesarExplanation;
            }
            else if (type == CurrentHelp::RailExplanation) {
               textures->currentHelp = CurrentHelp::RailExplanation;
            }
            else if (type == CurrentHelp::PigpenExplanation) {
               textures->currentHelp = CurrentHelp::PigpenExplanation;
            }
            else if (type == CurrentHelp::MorseExplanation) {
               textures->currentHelp = CurrentHelp::MorseExplanation;
            }
            else if (type == CurrentHelp::HexExplanation) {
               textures->currentHelp = CurrentHelp::HexExplanation;
            }
            else if (type == CurrentHelp::AlanTuring) {
               textures->currentHelp = CurrentHelp::AlanTuring;
            }
            else if (type == CurrentHelp::None) {
               textures->currentHelp = CurrentHelp::None;
            }
            break;
         case SDL_MOUSEMOTION:
            currentSprite = coloredSprite;
            break;
         }
      }
   }
}