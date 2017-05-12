#pragma once

class AdaInterfaceButtons {
public:
   AdaInterfaceButtons(int x, int y, int button, CurrentHelp buttonType);

   void handleEvents(SDL_Event* e, Textures* textures);

   void render(Window* window, Textures* textures);
   
private:
   CurrentHelp type;

   SDL_Point position;

   int currentSprite, lastSprite, coloredSprite;
};