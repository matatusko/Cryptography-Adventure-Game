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
#include "Constants.h"

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
   AdaInterface,
   RailDialog,
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

enum class CurrentHelp {
   CaesarExplanation,
   RailExplanation,
   PigpenExplanation,
   MorseExplanation,
   HexExplanation,
   AdaHelpWindow,
   None
};

struct Obstacles {
   Obstacles(SDL_Rect pos_) {
      pos = pos_;
   }
   SDL_Rect pos;
};

struct Textures {
   // Main world textures
   Texture worldmap;
   Texture objects;
   Texture character;
   Texture home;
   // NPCs textures
   Texture npc;
   SDL_Rect NPCspritesAvailable[24];
   Texture npcDialogText[constants::NPC_DIALOGUE_NUM];
   Texture dialogBox;
   // ADA
   Texture ada;
   Texture adaInitializationDialog[3];
   // Alphabet for different puzzles
   Texture alphabet;
   SDL_Rect alphabetLetters[26];
   // Rail cipher textures
   Texture railCipher;
   Texture AdaRailCipherScreen;
   Texture adaRailDialog[7];
   SDL_Rect railButtons[60];
   // Caesar cipher textures
   Texture ada_screen;
   Texture start_state;
   Texture state_3;
   Texture state_4;
   Texture state_5;
   Texture state_6;
   Texture state_7;
   Texture caesarButtonsSpritesheet;
   SDL_Rect caesarButtons[21];
   // Ada Interface Textures
   Texture adaHelpWindow;
   Texture caesarExplanation;
   Texture railExplanation;
   Texture pigpenExplanation;
   Texture morseExplanation;
   Texture hexExplanation;
   Texture interfaceButtonsSpritesheet;
   SDL_Rect interfaceButtons[14];
   CurrentHelp currentHelp;
};
typedef struct Textures Textures;

// Somehow Character class wouldn't recognize the Textures structures if it was included beforehand
// I suppose the reason behind this is that each of the following cpp files use the Textures structures
#include "Character.h"
#include "npc.h"
#include "Ada.h"
#include "Rail.h"
#include "Caesar.h"
#include "Alphabet.h"
#include "AdaInterfaceButtons.h"

struct Puzzles {
   // Variables related to the rail cipher
   std::vector<Alphabet> railAlphabet;
   std::vector<Rail> rail;
   // Varaibles related to the caaesar cipher
   std::vector<Caesar> caesar;
};
typedef struct Puzzles Puzzles;

struct GameObjects {
   // All the varaibles related to character needed for the main game loop
   Character character;
   int playerPositionX, playerPositionY;
   int currentAnimation;
   Interaction interactionFlag;
   // Ada variables;
   Ada ada;
   int adaPositionX, adaPositionY;
   int adaInitializationDialog;
   int adaCurrentRailDialog;
   // Camera and Dialog window
   SDL_Rect camera;
   SDL_Rect dialogViewport;
   int currentNPCdialog;
   // All the Obstacles and NPCs in the game
   std::vector<Obstacles> obstacles;
   std::vector<Npc> npcs;
   // Ada Interface
   std::vector<AdaInterfaceButtons> AdaInterfaceButtons;
   
};
typedef struct GameObjects GameObjects;

// Game logic functions:
void getPreMovementVariables(GameObjects* gameObjects);
void gameLoop(Textures* textures, Window* window, Puzzles* puzzles, GameObjects* gameObjects);
void cameraFocus(GameObjects* gameObjects);
int animateCharacter(GameObjects* gameObjects);
bool mainCollisionFunction(SDL_Rect rect1, const SDL_Rect rect2);
void checkForCollisionsWithObstacles(GameObjects* gameObjects);
Interaction checkForInteraction(GameObjects* gameObjects);

// Rendering functions
void renderEverything(Window* window, Textures* textures, GameObjects* gameObjects, Puzzles* puzzles, SDL_Event &e);
void renderMainGameScreen(Window* window, Textures* textures, GameObjects* gameObjects, Puzzles* puzzles);
void renderHome(Window* window, Textures* textures, GameObjects* gameObjects);
void renderWorld(Window* window, Textures* textures, GameObjects* gameObjects);
void renderNPCDialogs(Window* window, Textures* textures, GameObjects* gameObjects);
void renderRailCipher(Window* window, Textures* textures, GameObjects* gameObjects, Puzzles* puzzles, SDL_Event &e);
void renderCaesarCipher(Window* window, Textures* textures, GameObjects* gameObjects, Puzzles* puzzles);
void renderAdaDialogs(Window* window, Textures* textures, GameObjects* gameObjects);
void renderAdaInterface(Window* window, Textures* textures, GameObjects* gameObjects);

// Events functions:
void handleInteractionInput(SDL_Event &e, GameObjects* gameObjects);
void handlePuzzleAndInterfaceEvents(SDL_Event &e, GameObjects* gameObjects, Puzzles* puzzles, Textures* textures);
void handleTheMovementAndCollisions(SDL_Event& e, Textures* textures, GameObjects* gameObjects);

// Initialization functions:
bool loadMedia(Textures *textures, Window *window);
bool initializeVariables(Textures* textures, Window* window, Puzzles* puzzles, GameObjects* gameObjects);
void setObstacles(GameObjects* gameObjects);

void cutNPCSpritesheet(Textures* textures);
void setNpc(GameObjects* gameObjects);
void getNPCDialog(Window* window, Textures* textures);
void getAdaInitializationDialog(Window* window, Textures* textures);
void setAdaInterfaceButtons(GameObjects* gameObjects, Textures* textures);

void cutRailSpritesheet(Textures* textures);
void setRailSpritesPosition(Textures* textures, Puzzles* puzzles);
void getAdaRailDialog(Window *window, Textures* textures);

void cutCaesarButtons(Textures* textures);
void setCaesarSpritesPosition(Textures* textures, Puzzles* puzzles);

void cutAlphabetSpritesheet(Textures* textures);
void setAlphabetPositionForRail(Textures* textures, Puzzles* puzzles);

void cutInterfaceSpritesheet(Textures* textures);

// MISC
void automaticCollisions(SDL_Event &e, GameObjects* gameObjects);