#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <sstream>
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
   RailCipher,
   CaesarCipher,
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

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 2,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = BUTTON_SPRITE_MOUSE_OUT+1*7,
	BUTTON_SPRITE_MOUSE_DOWN = BUTTON_SPRITE_MOUSE_OUT+2*7,
	//BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 7
};

struct Textures {
   Texture worldmap;
   Texture objects;
   Texture character;
   Texture home;
   // npc stuff
   Texture npc;
   SDL_Rect NPCspritesAvailable[24];
   Texture npcDialogText[6];
   Texture dialogBox;
   // ada stuff
   Texture ada;
   Texture adaInitializationDialog[3];
   // Rail cipher stuff
   Texture railCipher;
   Texture AdaRailCipherScreen;
   SDL_Rect railButtons[60];

   // Caesar cipher stuff
   Texture ada_screen;
   Texture start_state;
   Texture state_3;
   Texture state_4;
   Texture state_5;
   Texture state_6;
   Texture state_7;
   Texture caesarButtonsSpritesheet;
   SDL_Rect caesarButtons[21];
};
typedef struct Textures Textures;
// Somehow Character class wouldn't recognize the Textures structures if it was included beforehand
#include "Character.h"
#include "npc.h"
#include "Ada.h"
#include "Rail.h"
#include "Caesar.h"

bool loadMedia(Textures *textures, Window *window);
void gameLoop(Textures* textures, Window* window);
void cameraFocus(SDL_Rect* camera, Character* character);
int animateCharacter(Character* character);
void setObstacles(std::vector<Obstacles>* obstacles);
bool checkCollision(SDL_Rect rect1, const SDL_Rect rect2);
void renderHome(Window* window, Textures* textures, SDL_Rect* camera);
void renderWorld(Window* window, Textures* textures, Character* character, SDL_Rect* camera, std::vector<Npc> npcs,
   int* currentAnimation);
void cutNPCSpritesheet(Textures* textures);
void setNpc(std::vector<Npc>* npc);
void checkForObjectsCollision(Character *character, Ada* ada, std::vector<Obstacles> obstacles, std::vector<Npc> npc,
   int playerPositionX, int playerPositionY, int adaPositionX, int adaPositionY);
Interaction checkForInteraction(Character *character, Ada* ada, std::vector<Npc> npc);
void getNPCDialog(Window* window, Textures* textures);
void getAdaInitializationDialog(Window* window, Textures* textures);
void StartAdaInitializationEvent(Window* window, Textures* textures, Ada* ada, int currentAdaDialog);
void cutRailSpritesheet(Textures* textures);
void setRailSpritesPosition(Textures* textures, std::vector<Rail>* rail);
void automaticCollisions(SDL_Event &e, Character* character);
void cutCaesarButtons(Textures* textures);
void setCaesarSpritesPosition(Textures* textures, std::vector<Caesar>* caesar);