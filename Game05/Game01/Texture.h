#pragma once
#include "Main.h"
#include "Window.h"

class Texture
{
   public:
      // Initialize the variables
      Texture();

      // Deallocate memory
      ~Texture();

      // Load image or text from a specified file path or string
      bool loadFromFile(std::string file_path, Window* window);
      bool loadFromText(Window* window, SDL_Color textColor, SDL_Color backgroundColor, std::string textureText);

      // Deallocate texture
      void free();

      void setBlendMode(SDL_BlendMode blending);
      void setAlpha(Uint8 alpha);
      void setColor(Uint8 red, Uint8 green, Uint8 blue);

      // Render the texture
      void render(
         Window* window,
         int pos_x,
         int pos_y,
         SDL_Rect* clip = NULL,
         double angle = 0.0,
         SDL_Point* center = NULL,
         SDL_RendererFlip flip = SDL_FLIP_NONE
      );

      // Get the dimenstions of an image
      int getWidth();
      int getHeight();
      SDL_Texture* getTexture();

   private:
      // Texture will be stored here
      SDL_Texture* texture;

      // texture dimensions
      int texture_width;
      int texture_height;
};