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
#define TILE_SIZE 32

enum class Location {
   Home,
   World,
};

struct Obstacles {
   Obstacles(SDL_Rect pos_) {
      pos = pos_;
   }
   SDL_Rect pos;
};

struct Textures {
   Texture worldmap;
   Texture character;
   Texture home;
};
typedef struct Textures Textures;
// Somehow Character class wouldn't recognize the Textures structures if it was included beforehand
#include "Character.h"

bool loadMedia(Textures *textures, Window *window);
void gameLoop(Textures* textures, Window* window);
void cameraFocus(SDL_Rect* camera, Character* character);
int animateCharacter(Character* character);
void setObstacles(std::vector<Obstacles>* obstacles);
bool checkCollision(SDL_Rect rect1, const SDL_Rect rect2);