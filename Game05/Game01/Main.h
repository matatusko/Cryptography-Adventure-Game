#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
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

enum class Interaction {
   Npc,
   AdaInitialization,
   Puzzle,
   None
};

enum class Direction {
   Up = 8,
   Down = 0,
   Right = 4,
   Left = 12,
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
   Texture npc;
   SDL_Rect NPCspritesAvailable[24];
   Texture npcDialogText[5];
   Texture dialogBox;
   Texture ada;
   Texture adaInitializationDialog[3];
};
typedef struct Textures Textures;
// Somehow Character class wouldn't recognize the Textures structures if it was included beforehand
#include "Character.h"
#include "npc.h"
#include "Ada.h"

bool loadMedia(Textures *textures, Window *window);
void gameLoop(Textures* textures, Window* window);
void cameraFocus(SDL_Rect* camera, Character* character);
int animateCharacter(Character* character);
void setObstacles(std::vector<Obstacles>* obstacles);
bool checkCollision(SDL_Rect rect1, const SDL_Rect rect2);
void renderHome(Window* window, Textures* textures, SDL_Rect* camera);
void renderWorld(Window* window, Textures* textures, Character* character, SDL_Rect* camera, std::vector<Npc> npcs);
void cutNPCSpritesheet(Textures* textures);
void setNpc(std::vector<Npc>* npc);
void checkForObjectsCollision(Character *character, Ada* ada, std::vector<Obstacles> obstacles, std::vector<Npc> npc,
   int playerPositionX, int playerPositionY, int adaPositionX, int adaPositionY);
Interaction checkForInteraction(Character *character, Ada* ada, std::vector<Npc> npc);
void getNPCDialog(Window* window, Textures* textures);
void getAdaInitializationDialog(Window* window, Textures* textures);
void StartAdaInitializationEvent(Window* window, Textures* textures, Ada* ada, int currentAdaDialog);