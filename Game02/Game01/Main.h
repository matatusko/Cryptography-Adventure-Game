#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Window.h"
#include "Texture.h"

// Map and camera related definitions
#define MAP_WIDTH 3840
#define MAP_HEIGHT 2240
#define CAMERA_WIDTH 1280
#define CAMERA_HEIGHT 720

// Sprites and textures definitions
#define CHARACTER_WIDTH 32
#define CHARACTER_HEIGHT 32
#define CHARACTER_VELOCITY 32

struct Textures {
   Texture background;
   Texture character;
};
typedef struct Textures Textures;
// Somehow Character class wouldn't recognize the Textures structures if it was included beforehand
#include "Character.h"

bool loadMedia(Textures *textures, Window *window);
void gameLoop(Textures* textures, Window* window);
void cameraFocus(SDL_Rect* camera, Character* character);
int animateCharacter(Character* character);