#include "Main.h"
#include "Texture.h"

Texture::Texture()
{
   // Initialize texture variables to null
   texture = NULL;
   texture_height = 0;
   texture_width = 0;
}

Texture::~Texture()
{
   // Deallocate the memory
   free();
}

bool Texture::loadFromFile(std::string file_path, Window* window)
{
   // Set the success flag
   bool success = false;

   // First, deallocate memory from any pre-existing texture
   free();

   // Create texture variable which will store the texture we are creating
   SDL_Texture* newTexture = NULL;

   // SDL doesn't support textures directly, so the idea is to use SDL_Surface to load the
   // image and later create a texture out of it
   SDL_Surface* loadedImage = IMG_Load(file_path.c_str());

   // Check if the image was loaded correctly. If not return false and print the error message
   if (loadedImage == NULL) {
      std::cout << "Unable to load image: " << file_path.c_str() << IMG_GetError() << std::endl;
      return success;
   }

   // Set the key color (not sure if necessary?)
   SDL_SetColorKey(loadedImage, SDL_TRUE, SDL_MapRGB(loadedImage->format, 0, 0xFF, 0xFF));

   // Now we use our surface with image to make a texture out of it
   newTexture = SDL_CreateTextureFromSurface(window->renderer, loadedImage);

   // And check for potential error
   if (newTexture == NULL) {
      std::cout << "Unable to create texture from: " << file_path.c_str() << IMG_GetError() << std::endl;
      return success;
   }

   // Lastly, get the image dimensions into the class
   texture_width = loadedImage->w;
   texture_height = loadedImage->h;

   // And get rid of the temp surface and return success if the texture is not null
   SDL_FreeSurface(loadedImage);
   texture = newTexture;
   return texture != NULL;
}

void Texture::render(Window* window, int x_pos, int y_pos, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
   // Create a rectangular with proper size and location to where it will be later rendered
   SDL_Rect renderQuad = { x_pos, y_pos, texture_width, texture_height };

   // Clip the rendered image if necessary (for the use of camera?)
   if (clip != NULL) {
      renderQuad.w = clip->w;
      renderQuad.h = clip->h;
   }

   // Render to screen
   SDL_RenderCopyEx(window->renderer, texture, clip, &renderQuad, angle, center, flip);
}

bool Texture::loadFromText(Window* window, SDL_Color textColor, SDL_Color backgroundColor, std::string textureText)
{
   // Get rid of any preexisting texture
   free();

   // Render text surface
   SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(window->font, textureText.c_str(), textColor, 550);
   if (textSurface == NULL) {
      std::cout << "Failed to render text surface! : " << TTF_GetError() << std::endl;
      return false;
   }
   texture = SDL_CreateTextureFromSurface(window->renderer, textSurface);
   if (texture == NULL) {
      std::cout << "Failed to create texture from rendered text! : " << SDL_GetError() << std::endl;
      return false;
   }
   // Get texture dimensions
   texture_width = textSurface->w;
   texture_height = textSurface->h;
   
   // Get rid of now unneccessary surface
   SDL_FreeSurface(textSurface);

   return true;
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
   SDL_SetTextureBlendMode(texture, blending);
}

void Texture::setAlpha(Uint8 alpha)
{
   SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
   SDL_SetTextureColorMod(texture, red, green, blue);
}

int Texture::getWidth()
{
   return texture_width;
}

int Texture::getHeight()
{
   return texture_height;
}

void Texture::free()
{
   if (texture != NULL) {
      SDL_DestroyTexture(texture);
      texture = NULL;
      texture_height = 0;
      texture_width = 0;
   }
}

SDL_Texture* Texture::getTexture()
{
   return texture;
}