#include "Main.h"

void setObstacles(std::vector<Obstacles>* obstacles)
{
   obstacles->push_back(Obstacles({ 0, 2040, 745, 200 })); // bottom-left forest
   obstacles->push_back(Obstacles({ 0, 630, 350, 850 })); // left-side water and trees up to 2 houses
   obstacles->push_back(Obstacles({ 310, 460, 135, 140 })); // bridge left area
   obstacles->push_back(Obstacles({ 0, 1520, 530, 130 })); // left area around 2 houses
}

void setNpc(std::vector<Npc>* npc)
{
   npc->push_back(Npc(320, 1632, rand() % 24));
   npc->push_back(Npc(704, 1632, rand() % 24));
   npc->push_back(Npc(1056, 1632, rand() % 24));
   npc->push_back(Npc(1024, 1632, rand() % 24));
   npc->push_back(Npc(1376, 2016, rand() % 24));
   npc->push_back(Npc(1792, 1824, rand() % 24));
   npc->push_back(Npc(2784, 1760, rand() % 24));
   npc->push_back(Npc(3328, 288, rand() % 24));
   npc->push_back(Npc(3296, 288, rand() % 24));
   npc->push_back(Npc(1856, 32, rand() % 24));
   npc->push_back(Npc(1888, 32, rand() % 24));
   npc->push_back(Npc(1920, 32, rand() % 24));
   npc->push_back(Npc(1952, 32, rand() % 24));
   npc->push_back(Npc(1984, 32, rand() % 24));
   npc->push_back(Npc(1440, 384, rand() % 24));
   npc->push_back(Npc(1184, 544, rand() % 24));
   npc->push_back(Npc(1216, 544, rand() % 24));
   npc->push_back(Npc(320, 320, rand() % 24));
   npc->push_back(Npc(128, 1088, rand() % 24));
   npc->push_back(Npc(384, 608, rand() % 24));
   npc->push_back(Npc(672, 832, rand() % 24));
   npc->push_back(Npc(640, 864, rand() % 24));
   npc->push_back(Npc(704, 864, rand() % 24));
   npc->push_back(Npc(1024, 1152, rand() % 24));
   npc->push_back(Npc(160, 1664, rand() % 24));
   npc->push_back(Npc(1024, 1888, rand() % 24));
   npc->push_back(Npc(1216, 1888, rand() % 24));
   npc->push_back(Npc(960, 2016, rand() % 24));
   npc->push_back(Npc(1728, 1280, rand() % 24));
   npc->push_back(Npc(2048, 1152, rand() % 24));
   npc->push_back(Npc(2272, 992, rand() % 24));
   npc->push_back(Npc(1696, 864, rand() % 24));
   npc->push_back(Npc(1600, 576, rand() % 24));
   npc->push_back(Npc(1600, 256, rand() % 24));
   npc->push_back(Npc(1632, 224, rand() % 24));
   npc->push_back(Npc(2528, 1056, rand() % 24));
   npc->push_back(Npc(2944, 1376, rand() % 24));
   npc->push_back(Npc(2880, 1376, rand() % 24));
   npc->push_back(Npc(3200, 1856, rand() % 24));
   npc->push_back(Npc(1616, 1792, rand() % 24));
   npc->push_back(Npc(3520, 1376, rand() % 24));
   npc->push_back(Npc(3488, 1376, rand() % 24));
   npc->push_back(Npc(3488, 736, rand() % 24));
   npc->push_back(Npc(3360, 736, rand() % 24));
}

void getNPCDialog(Window* window, Textures* textures)
{
   SDL_Color dialogColor = { 0, 0, 0 };
   SDL_Color backgroundColor = { 255, 255, 255 };
   if (!(textures->npcDialogText[0].loadFromText(window, dialogColor, backgroundColor,
      "Did you know? Computing industry boasts one of the highest starting salaries for new college graduates!"))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->npcDialogText[1].loadFromText(window, dialogColor, backgroundColor,
      "Alan Turing the father of computer science, artificial intelligence and who helped break German WW2 cyphers, \
committed suicide after being forced to undergo hormonal treatment for homosexuality and \
barred from continuing his cryptographic work."))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->npcDialogText[2].loadFromText(window, dialogColor, backgroundColor,
      "A 15 year old hacked NASA computers and caused a 21-day shutdown of their computers. \
He hacked Pentagon weapons computer too…"))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->npcDialogText[3].loadFromText(window, dialogColor, backgroundColor,
      "U.S. chose 00000000 as the password for its computer controls of nuclear tipped missiles for eight years."))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->npcDialogText[4].loadFromText(window, dialogColor, backgroundColor,
      "CAPTCHA is an acronym for \"Completely Automated Public Turing test to tell Computers and Humans Apart\""))) {
      printf("Failed to render text texture!\n");
      return;
   }
}

void cutNPCSpritesheet(Textures* textures)
{
   int next_x = 0, next_y = 0, current_index = 0;
   for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 6; j++) {
         textures->NPCspritesAvailable[current_index].x = next_x;
         textures->NPCspritesAvailable[current_index].y = next_y;
         textures->NPCspritesAvailable[current_index].w = TILE_SIZE;
         textures->NPCspritesAvailable[current_index].h = TILE_SIZE;
         next_x += TILE_SIZE;
         current_index++;
      }
      next_x = 0;
      next_y += TILE_SIZE;
   }
}