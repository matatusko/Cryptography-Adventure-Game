#include "Main.h"
using namespace std;

struct locations
{
   int x;
   int y;
   int x1;
   int y1;
   int height;
   int width;
   string hede = "";
   string comment = "";
};
typedef locations Locations;

void automaticCollisions(SDL_Event &e, GameObjects* gameObjects) {

   Locations loc;

   if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
   {

      stringstream ss;
      switch (e.key.keysym.sym)
      {
         //first location = x;
      case SDLK_x:

         loc.x = gameObjects->character.getPosX();
         loc.y = gameObjects->character.getPosY();



         cout << "pos X :" << loc.x << " pos Y :" << loc.y << endl;
         break;
         // Handle the character events including movement and collision checks

         //for second location press y
      case SDLK_y:

         loc.x1 = gameObjects->character.getPosX();
         loc.y1 = gameObjects->character.getPosY();
         cout << "pos X1 :" << loc.x1 << " pos Y1 :" << loc.y1 << endl;
         break;

         //for recording , press t, after press t, go to console, write a command without //
      case SDLK_t:


         cout << "pos X1 :" << loc.x1 << " pos Y1 :" << loc.y1 << endl;
         loc.height = abs(loc.y1 - loc.y) + 1;
         loc.width = abs(loc.x1 - loc.x) + 1;

         loc.comment = "no comment";
         //cin >>loc.comment;
         ss << "obstacles->push_back(Obstacles({" << loc.x << "," << loc.y << "," << loc.width << "," << loc.height << "}));//" << loc.comment << "\n";
         loc.hede += ss.str();

         cout << "width" << loc.width << "  " << "height" << loc.height << endl;

         break;
         //when you are done, press k for recording collisions to txt.file
      case SDLK_k:
         printf("k pressed\n");
         ofstream myfile;
         myfile.open("collisions.txt");
         myfile << loc.hede;
         myfile.close();
         break;

      }

   }
}