#include "Main.h"

bool initializeVariables(Textures* textures, Window* window, Puzzles* puzzles, GameObjects* gameObjects)
{
   // Set the initial interaction flag to none
   gameObjects->interactionFlag = Interaction::None;
   textures->currentHelp = CurrentHelp::AdaHelpWindow;

   // Set the storyline dialogs to 0
   gameObjects->adaInitializationDialog = 0;
   gameObjects->adaCurrentRailDialog = 0;

   // Initialize Rail Cipher
   setAlphabetPositionForRail(textures, puzzles);
   setRailSpritesPosition(textures, puzzles);
   getAdaRailDialog(window, textures);
   gameObjects->isRailCompleted = false;

   // Initialize Caesar Cipher
   setCaesarSpritesPosition(textures, puzzles);

   // Initialize Morse Cipher
   setMorseSpritesPosition(textures, puzzles);
   setAlphabetPositionForMorse(textures, puzzles);
   gameObjects->isRailCompleted = false;

   // Initialize Ada interface buttons
   setAdaInterfaceButtons(gameObjects, textures);

   // Create the camera rectangle at position 0, 0 with camera's features
   gameObjects->camera = { 0, 0, CAMERA_WIDTH, CAMERA_HEIGHT };

   // Create the dialog window
   gameObjects->dialogViewport = { 64, 64, 600, 150 };

   // Initialize the frames for rendering animations
   gameObjects->currentAnimation = 0;

   // Initialize the obstacles and nps and all of their locatations
   setObstacles(gameObjects);
   setNpc(gameObjects);

   return true;
}

void setNpc(GameObjects* gameObjects)
{
   gameObjects->npcs.push_back(Npc(320, 1632, rand() % 24));
   gameObjects->npcs.push_back(Npc(704, 1632, rand() % 24));
   gameObjects->npcs.push_back(Npc(1056, 1632, rand() % 24));
   gameObjects->npcs.push_back(Npc(1024, 1632, rand() % 24));
   gameObjects->npcs.push_back(Npc(1376, 2016, rand() % 24));
   gameObjects->npcs.push_back(Npc(1792, 1824, rand() % 24));
   gameObjects->npcs.push_back(Npc(2784, 1760, rand() % 24));
   gameObjects->npcs.push_back(Npc(3328, 288, rand() % 24));
   gameObjects->npcs.push_back(Npc(3296, 288, rand() % 24));
   gameObjects->npcs.push_back(Npc(1856, 32, rand() % 24));
   gameObjects->npcs.push_back(Npc(1888, 32, rand() % 24));
   gameObjects->npcs.push_back(Npc(1920, 32, rand() % 24));
   gameObjects->npcs.push_back(Npc(1952, 32, rand() % 24));
   gameObjects->npcs.push_back(Npc(1984, 32, rand() % 24));
   gameObjects->npcs.push_back(Npc(1440, 384, rand() % 24));
   gameObjects->npcs.push_back(Npc(1184, 544, rand() % 24));
   gameObjects->npcs.push_back(Npc(1216, 544, rand() % 24));
   gameObjects->npcs.push_back(Npc(320, 320, rand() % 24));
   gameObjects->npcs.push_back(Npc(128, 1088, rand() % 24));
   gameObjects->npcs.push_back(Npc(384, 608, rand() % 24));
   gameObjects->npcs.push_back(Npc(672, 832, rand() % 24));
   gameObjects->npcs.push_back(Npc(640, 864, rand() % 24));
   gameObjects->npcs.push_back(Npc(704, 864, rand() % 24));
   gameObjects->npcs.push_back(Npc(1024, 1152, rand() % 24));
   gameObjects->npcs.push_back(Npc(160, 1664, rand() % 24));
   gameObjects->npcs.push_back(Npc(1024, 1888, rand() % 24));
   gameObjects->npcs.push_back(Npc(1216, 1888, rand() % 24));
   gameObjects->npcs.push_back(Npc(960, 2016, rand() % 24));
   gameObjects->npcs.push_back(Npc(1728, 1280, rand() % 24));
   gameObjects->npcs.push_back(Npc(2048, 1152, rand() % 24));
   gameObjects->npcs.push_back(Npc(2272, 992, rand() % 24));
   gameObjects->npcs.push_back(Npc(1696, 864, rand() % 24));
   gameObjects->npcs.push_back(Npc(1600, 576, rand() % 24));
   gameObjects->npcs.push_back(Npc(1600, 256, rand() % 24));
   gameObjects->npcs.push_back(Npc(1632, 224, rand() % 24));
   gameObjects->npcs.push_back(Npc(2528, 1056, rand() % 24));
   gameObjects->npcs.push_back(Npc(2944, 1376, rand() % 24));
   gameObjects->npcs.push_back(Npc(2880, 1376, rand() % 24));
   gameObjects->npcs.push_back(Npc(3200, 1856, rand() % 24));
   gameObjects->npcs.push_back(Npc(1600, 1792, rand() % 24));
   gameObjects->npcs.push_back(Npc(3520, 1376, rand() % 24));
   gameObjects->npcs.push_back(Npc(3488, 1376, rand() % 24));
   gameObjects->npcs.push_back(Npc(3488, 736, rand() % 24));
   gameObjects->npcs.push_back(Npc(3360, 736, rand() % 24));
}

void getNPCDialog(Window* window, Textures* textures)
{
   SDL_Color dialogColor = { 0, 0, 0 };
   if (!(textures->npcDialogText[0].loadFromText(window, dialogColor,
      "My dad said that computer scientists make the most money... but I don't believe him'"))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->npcDialogText[1].loadFromText(window, dialogColor,
      "I heard a mathematician called ADA LOVELACE thought about the first computer programs in the 1830s! Can you believe it?"))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->npcDialogText[2].loadFromText(window, dialogColor,
      "I've heard a 15 year old once hacked the computers at NASA and caused a 21-day shutdown of their computers. \
He hacked Pentagon weapons computer too! Kids are geniuses these days..."))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->npcDialogText[3].loadFromText(window, dialogColor,
      "Did you know that the American government chose 00000000 as the password to launch nuclear missiles for eight years?! Crazy dangerous, with password like this!"))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->npcDialogText[4].loadFromText(window, dialogColor,
      "I read that CAPTCHA is an acronym for \"Completely Automated Public Turing test to tell Computers and Humans Apart\"... Turing... I recognise that name..."))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->npcDialogText[6].loadFromText(window, dialogColor,
      "My mum said I have to stop talking so much about memory and RAM, but what she doesen't know is that memory IS RAM!"))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->npcDialogText[5].loadFromText(window, dialogColor,
      "Apparently the first computer was called ENIAC and weighted more than 27 tons, taking up to 1800 square feet?! That's more than a huge track!"))) {
      printf("Failed to render text texture!\n");
      return;
   }
}

void getAdaInitializationDialog(Window* window, Textures* textures)
{
   SDL_Color dialogColor = { 255, 0, 0 };
   if (!(textures->adaInitializationDialog[0].loadFromText(window, dialogColor,
      "BZzzzZr... WARREUUUM... \nP-please.. Power. up.. wERRRRRUM"))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->adaInitializationDialog[1].loadFromText(window, dialogColor,
      "Puzzle will go here."))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->adaInitializationDialog[2].loadFromText(window, dialogColor,
      "Wow, thanks! Hello World! You decrypted the caesar cipher, well done!\n\
My name is A.D.A - Advanced Digital Automation, I am a last creation of a first computer scientist, Ada Lovelace."))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->adaInitializationDialog[3].loadFromText(window, dialogColor,
      "Did you know that in this little town all the greatest mind in computer science throughtout \
history did some of their best work?"))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->adaInitializationDialog[4].loadFromText(window, dialogColor,
      "All of them somewhat contributed to the creation of a perfect machine!\n\
I know its hidden somewhere around in this town, although I do know what where or what it is! :(\n"))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->adaInitializationDialog[5].loadFromText(window, dialogColor,
   "You cracked the caesar cipher on your own, how about you give it a shot and look for my creator's final secret \
together with me? I sense 4 different secret codes scattered across the town."))) {
      printf("Failed to render text texture!\n");
   return;
   }
   if (!(textures->adaInitializationDialog[6].loadFromText(window, dialogColor,
      "Knowing my creator, all of the codes are encrypther via different ciphers, but I'm sure you can crack them all!\n\
In case you need some help with certain puzzle, you can access my console by hitting ESC button."))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->adaInitializationDialog[7].loadFromText(window, dialogColor,
      "Also, check out the profile section in my console interface to learn more about the greates computer scientists!\n\
\nGood luck!"))) {
      printf("Failed to render text texture!\n");
      return;
   }
}

void getAdaRailDialog(Window *window, Textures* textures) 
{
   SDL_Color dialogColor = { 255, 0, 0 };
   if (!(textures->adaRailDialog[0].loadFromText(window, dialogColor,
      "Wrrruum! It appears my creator has left a message here!\nGive me a second, I will download it..."))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->adaRailDialog[1].loadFromText(window, dialogColor,
      "1... 2... 3... Downloading... \nFINISHED"))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->adaRailDialog[2].loadFromText(window, dialogColor,
      "I got the message, however it appears to be encrypther using a mix of rail and pigpen cipher :(\nBut I'm sure you can break the code."))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->adaRailDialog[3].loadFromText(window, dialogColor,
      "Remember, you can press ESC key to access my console anytime and get help with various ciphers.\n\nGOOD LUCK!"))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->adaRailDialog[4].loadFromText(window, dialogColor,
      "PUZZLE GOES HERE"))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->adaRailDialog[5].loadFromText(window, dialogColor,
      "Good job! The code reads: ALAN TURING. \n... Oh, Alan! I remember him, a great mathematician and cryptographer."))) {
      printf("Failed to render text texture!\n");
      return;
   }
   if (!(textures->adaRailDialog[6].loadFromText(window, dialogColor,
      "You can read more about his achievements using my interface by pressing ESC key.\n\n\
Remember his name, I've got a feeling it will be needed for the final puzzle!"))) {
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

bool loadMedia(Textures *textures, Window *window)
{
   // Set success flag
   bool success = true;

   // Load the background texture
//   if (!(textures->worldmap.loadFromFile("images/map.png", window))) {
//     std::cout << "Failed to load the map texture" << std::endl;
//     success = false;
//   }

   // Load the background texture
   if (!(textures->worldmap.loadFromFile("images/ground.png", window))) {
      std::cout << "Failed to load the map texture" << std::endl;
      success = false;
   }

   // Load the background texture
   if (!(textures->objects.loadFromFile("images/collision.png", window))) {
      std::cout << "Failed to load the map texture" << std::endl;
      success = false;
   }

   // Load the character texture
   if (!(textures->character.loadFromFile("images/character.png", window))) {
      std::cout << "Failed to load the character texture" << std::endl;
      success = false;
   }

   // Load the home texture
   if (!(textures->home.loadFromFile("images/room.png", window))) {
      std::cout << "Failed to load the home texture" << std::endl;
      success = false;
   }

   // Load the npc texture and cut it into SDL_Rects
   if (!(textures->npc.loadFromFile("images/NPC.png", window))) {
      std::cout << "Failed to load the npc texture" << std::endl;
      success = false;
   }
   cutNPCSpritesheet(textures);

   // Load the font type and set the texts to proper texture
   if (!(window->font = TTF_OpenFont("images/Consolas.ttf", 20))) {
      std::cout << "Failed to load the font" << std::endl;
      success = false;
   }
   getNPCDialog(window, textures);

   // Load the ada texture 
   if (!(textures->ada.loadFromFile("images/ada.png", window))) {
      std::cout << "Failed to load the npc texture" << std::endl;
      success = false;
   }
   getAdaInitializationDialog(window, textures);

   // Load the dialog box
   if (!(textures->dialogBox.loadFromFile("images/dialogBox.png", window))) {
      std::cout << "Failed to load the npc texture" << std::endl;
      success = false;
   }

   // Load the rail/pigpen puzzle screen
   if (!(textures->AdaRailCipherScreen.loadFromFile("images/rail_ada.png", window))) {
      std::cout << "Failed to load the rail cipher screen texture" << std::endl;
      success = false;
   }

   // Load the rail/pigpen puzzle itself
   if (!(textures->railCipher.loadFromFile("images/railSprites.png", window))) {
      std::cout << "Failed to load the rail/pigpen sprites texture" << std::endl;
      success = false;
   }
   cutRailSpritesheet(textures);

   // Load Caesar textures :
   // load Ada background
	if (!(textures->ada_screen.loadFromFile("images/caesar_img/ada_screen.png", window))) {
		std::cout << "Failed to load the ada_screen texture" << std::endl;
		success = false;
	}
      if (!(textures->start_state.loadFromFile("images/caesar_img/start_state.png", window))) {
		std::cout << "Failed to load the start_state texture" << std::endl;
		success = false;
	}
      if (!(textures->state_3.loadFromFile("images/caesar_img/state_3.png", window))) {
		std::cout << "Failed to load the state_3 texture" << std::endl;
		success = false;
	}
      if (!(textures->state_4.loadFromFile("images/caesar_img/state_4.png", window))) {
		std::cout << "Failed to load the state_4 texture" << std::endl;
		success = false;
	}
      if (!(textures->state_5.loadFromFile("images/caesar_img/state_5.png", window))) {
		std::cout << "Failed to load the state_5 texture" << std::endl;
		success = false;
	}
      if (!(textures->state_6.loadFromFile("images/caesar_img/state_6.png", window))) {
		std::cout << "Failed to load the state_6 texture" << std::endl;
		success = false;
	}
      if (!(textures->state_7.loadFromFile("images/caesar_img/state_7.png", window))) {
		std::cout << "Failed to load the state_7 texture" << std::endl;
		success = false;
	}
      if (!(textures->caesarButtonsSpritesheet.loadFromFile("images/caesar_img/c_buttons.png", window))) {
         std::cout << "Failed to load the state_7 texture" << std::endl;
         success = false;
      }
   cutCaesarButtons(textures);

   //Load Morse Code textures :
   //load Ada Background
	if (!(textures->morse_screen.loadFromFile("images/morse_img/morse.png", window))) {
		std::cout << "Failed to load the morse_screen texture" << std::endl;
		success = false;
	}
      // Load button spritesheet
      if (!(textures->morseButtonSpritesheet.loadFromFile("images/morse_img/audio_buttons.png", window))) {
		std::cout << "Failed to load the audio_buttons texture" << std::endl;
		success = false;
	}
      cutMorseButtons(textures);
      
   // Load the alphabet spritesheet
   if (!(textures->alphabet.loadFromFile("images/alphabet.png", window))) {
      std::cout << "Failed to load the alphabet texture" << std::endl;
      success = false;
   }
   cutAlphabetSpritesheet(textures);

   // Load Ada Interface Textures
   if (!(textures->adaHelpWindow.loadFromFile("images/Ada_interface/main_screen.png", window))) {
      std::cout << "Failed to load the ada interface screen" << std::endl;
      success = false;
   }
   if (!(textures->caesarExplanation.loadFromFile("images/Ada_interface/caesar.png", window))) {
      std::cout << "Failed to load the ada caesar help window" << std::endl;
      success = false;
   }
   if (!(textures->hexExplanation.loadFromFile("images/Ada_interface/hex.png", window))) {
      std::cout << "Failed to load the ada hex help window" << std::endl;
      success = false;
   }
   if (!(textures->morseExplanation.loadFromFile("images/Ada_interface/morse.png", window))) {
      std::cout << "Failed to load the ada morse help window" << std::endl;
      success = false;
   }
   if (!(textures->pigpenExplanation.loadFromFile("images/Ada_interface/pigpen.png", window))) {
      std::cout << "Failed to load the ada pigpen help window" << std::endl;
      success = false;
   }
   if (!(textures->railExplanation.loadFromFile("images/Ada_interface/rail.png", window))) {
      std::cout << "Failed to load the ada rail help window" << std::endl;
      success = false;
   }
   if (!(textures->alanTuringExplanation.loadFromFile("images/Ada_interface/alan.png", window))) {
      std::cout << "Failed to load the ada alan profile window" << std::endl;
      success = false;
   }
   if (!(textures->adaLovelaceExplanation.loadFromFile("images/Ada_interface/lovelace.png", window))) {
      std::cout << "Failed to load the ada lovelace profile window" << std::endl;
      success = false;
   }
   if (!(textures->charlesBabbageExplanation.loadFromFile("images/Ada_interface/babbage.png", window))) {
      std::cout << "Failed to load the ada alan profile window" << std::endl;
      success = false;
   }
   if (!(textures->interfaceButtonsSpritesheet.loadFromFile("images/Ada_interface/interfaceButtons.png", window))) {
      std::cout << "Failed to load the ada interface buttons" << std::endl;
      success = false;
   }
   cutInterfaceSpritesheet(textures);

   return success;
}

void cutRailSpritesheet(Textures* textures)
{
   // Cut the spritesheet
   for (int y = 0, curr = 0; y < 6; y++) {
      for (int x = 0; x < 10; x++, curr++)
      {
         textures->railButtons[curr].x = x * 66;
         textures->railButtons[curr].y = y * 66;
         textures->railButtons[curr].w = 66;
         textures->railButtons[curr].h = 66;
      }
   }
}

void cutInterfaceSpritesheet(Textures* textures)
{
   // Cut the spritesheet
   for (int y = 0, curr = 0; y < 10; y++) {
      for (int x = 0; x < 2; x++, curr++)
      {
         textures->interfaceButtons[curr].x = x * 133;
         textures->interfaceButtons[curr].y = y * 28;
         textures->interfaceButtons[curr].w = 133;
         textures->interfaceButtons[curr].h = 28;
      }
   }
}

void cutAlphabetSpritesheet(Textures* textures)
{
   // Cut the spritesheet
   for (int y = 0, curr = 0; y < 4; y++) {
      for (int x = 0; x < 8; x++, curr++)
      {
         if (curr >= 26) {
            break;
         }
         textures->alphabetLetters[curr].x = x * 54;
         textures->alphabetLetters[curr].y = y * 54;
         textures->alphabetLetters[curr].w = 54;
         textures->alphabetLetters[curr].h = 54;
      }
   }
}

//Letters for morse code
void cutLettersSpritesheet(Textures* textures)
{
   // Cut the spritesheet
   for (int y = 0, curr = 0; y < 4; y++) {
      for (int x = 0; x < 8; x++, curr++)
      {
         if (curr >= 26) {
            break;
         }
         textures->lettersLetters[curr].x = x * 100;
         textures->lettersLetters[curr].y = y * 100;
         textures->lettersLetters[curr].w = 100;
         textures->lettersLetters[curr].h = 100;
      }
   }
}

void setAlphabetPositionForMorse(Textures* textures, Puzzles* puzzles) 
{
   puzzles->morseAlphabet.push_back(Alphabet(600, 370, 0));
   puzzles->morseAlphabet.push_back(Alphabet(650, 370, 0));
   puzzles->morseAlphabet.push_back(Alphabet(700, 370, 0));

   puzzles->morseAlphabet.push_back(Alphabet(600, 540, 0));
   puzzles->morseAlphabet.push_back(Alphabet(650, 540, 0));
   puzzles->morseAlphabet.push_back(Alphabet(700, 540, 0));
   puzzles->morseAlphabet.push_back(Alphabet(750, 540, 0));
   puzzles->morseAlphabet.push_back(Alphabet(800, 540, 0));
}

void cutCaesarButtons(Textures* textures)
{

   for (int y = 0, curr = 0; y < 3; y++) {
      for (int x = 0; x < 7; x++, curr++)
      {
//         std::cout << "curr = " << curr << std::endl;
         textures->caesarButtons[curr].x = x*88;
         textures->caesarButtons[curr].y = y*88;
         textures->caesarButtons[curr].w = 88;
         textures->caesarButtons[curr].h = 88;
      }
//      std::cout << "endx" << curr << std::endl;
//      std::cout << "y" << y << std::endl;
   }
}

void cutMorseButtons(Textures* textures)
{


         textures->morseButton[0].x = 0;
         textures->morseButton[0].y = 0;
         textures->morseButton[0].w = 100;
         textures->morseButton[0].h = 100;

         textures->morseButton[1].x = 0;
         textures->morseButton[1].y = 100;
         textures->morseButton[1].w = 100;
         textures->morseButton[1].h = 100;

}

void setMorseSpritesPosition(Textures* textures, Puzzles* puzzles)
{
   puzzles->morse.push_back(Morse(450, 345, 0));
   puzzles->morse.push_back(Morse(450, 520, 1));
}

void setAdaInterfaceButtons(GameObjects* gameObjects, Textures* textures)
{
   gameObjects->AdaInterfaceButtons.push_back(AdaInterfaceButtons(50, 50, 0, CurrentHelp::AdaHelpWindow));
   gameObjects->AdaInterfaceButtons.push_back(AdaInterfaceButtons(200, 50, 2, CurrentHelp::CaesarExplanation));
   gameObjects->AdaInterfaceButtons.push_back(AdaInterfaceButtons(350, 50, 4, CurrentHelp::PigpenExplanation));
   gameObjects->AdaInterfaceButtons.push_back(AdaInterfaceButtons(500, 50, 6, CurrentHelp::RailExplanation));
   gameObjects->AdaInterfaceButtons.push_back(AdaInterfaceButtons(650, 50, 8, CurrentHelp::HexExplanation));
   gameObjects->AdaInterfaceButtons.push_back(AdaInterfaceButtons(800, 50, 10, CurrentHelp::MorseExplanation));
   gameObjects->AdaInterfaceButtons.push_back(AdaInterfaceButtons(950, 50, 12, CurrentHelp::None));

   gameObjects->AdaInterfaceButtons.push_back(AdaInterfaceButtons(50, 635, 16, CurrentHelp::AdaLovelace));
   gameObjects->AdaInterfaceButtons.push_back(AdaInterfaceButtons(200, 635, 18, CurrentHelp::CharlesBabbage));
}

void setRailSpritesPosition(Textures* textures, Puzzles* puzzles)
{
   //Set buttons in correct place
   int next_x = 70;
   int next_y = 50;
   int current_index = 0;
   for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 10; j++) {
         puzzles->rail.push_back(Rail(next_x, next_y, current_index));
         next_x += 66;
         current_index++;
      }
      next_x = 70;
      next_y += 66;
   }
   next_x = 70;
   next_y = 50;
   for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 10; j++) {
         puzzles->rail.push_back(Rail(next_x, next_y, current_index));
         next_x += 66;
         current_index++;
      }
      next_x = 70;
      next_y += 66;
   }
}

void setAlphabetPositionForRail(Textures* textures, Puzzles* puzzles)
{
   for (int i = 0, position = 170; i < 4; i++, position += 60) {
      puzzles->railAlphabet.push_back(Alphabet(position, 566, 0));
   }

   for (int i = 0, position = 450; i < 6; i++, position += 60) {
      puzzles->railAlphabet.push_back(Alphabet(position, 566, 0));
   }
}

void setCaesarSpritesPosition(Textures* textures, Puzzles* puzzles)
{
   puzzles->caesar.push_back(Caesar(316, 448, 0));
   puzzles->caesar.push_back(Caesar(272, 360, 1));
   puzzles->caesar.push_back(Caesar(360, 360, 2));
   puzzles->caesar.push_back(Caesar(228, 272, 3));
   puzzles->caesar.push_back(Caesar(316, 272, 4));
   puzzles->caesar.push_back(Caesar(404, 272, 5));
   puzzles->caesar.push_back(Caesar(316, 184, 6));
   puzzles->caesar.push_back(Caesar(316, 448, 7));
   puzzles->caesar.push_back(Caesar(272, 360, 8));
   puzzles->caesar.push_back(Caesar(360, 360, 9));
   puzzles->caesar.push_back(Caesar(228, 272, 10));
   puzzles->caesar.push_back(Caesar(316, 272, 11));
   puzzles->caesar.push_back(Caesar(404, 272, 12));
   puzzles->caesar.push_back(Caesar(316, 184, 13));
   puzzles->caesar.push_back(Caesar(316, 448, 14));
   puzzles->caesar.push_back(Caesar(272, 360, 15));
   puzzles->caesar.push_back(Caesar(360, 360, 16));
   puzzles->caesar.push_back(Caesar(228, 272, 17));
   puzzles->caesar.push_back(Caesar(316, 272, 18));
   puzzles->caesar.push_back(Caesar(404, 272, 19));
   puzzles->caesar.push_back(Caesar(316, 184, 20));
}

// void setMorseSpritesPosition(Textures* textures, Puzzles* puzzles)
// {
//       puzzles->morse.push_back(Caesar(316, 448, 0));
// }

void setObstacles(GameObjects* gameObjects)
{
   gameObjects->obstacles.push_back(Obstacles({ 0, 2040, 745, 200 })); // bottom-left forest
   gameObjects->obstacles.push_back(Obstacles({ 0, 630, 350, 850 })); // left-side water and trees up to 2 houses
   gameObjects->obstacles.push_back(Obstacles({ 310, 460, 135, 140 })); // bridge left area
   gameObjects->obstacles.push_back(Obstacles({ 0, 1520, 530, 130 })); // left area around 2 houses
                                                           //trees at the right of the main house
   gameObjects->obstacles.push_back(Obstacles({ 2208,1728,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2208,1632,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2304,1632,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2464,1632,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2464,1792,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2240,1760,1,1 }));//no comment

                                                      //house 
   gameObjects->obstacles.push_back(Obstacles({ 2048,1792,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2048,1696,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1952,1664,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1856,1728,1,1 }));//no comment

   gameObjects->obstacles.push_back(Obstacles({ 1888,1760,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1920,1728,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1984,1728,33,33 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2080,1728,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2080,1664,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2080,1792,1,1 }));//no comment

   gameObjects->obstacles.push_back(Obstacles({ 1888,1664,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1984,1664,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1888,1792,1,1 }));//no comment
                                                      //House and trees at the left
   gameObjects->obstacles.push_back(Obstacles({ 1920,1760,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1696,1760,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1664,1600,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1824,1600,1,1 }));//no comment

                                                      //trees  at the left and top left colorful
   gameObjects->obstacles.push_back(Obstacles({ 1152,192,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1280,192,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1408,192,1,1 }));//no comment

                                                     // addition to big two trees and one for house at the left
   gameObjects->obstacles.push_back(Obstacles({ 1696,1600,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 896,1568,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 704,1600,1,1 }));//no comment

                                                     // trees second right of the house
   gameObjects->obstacles.push_back(Obstacles({ 2720,1568,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2848,1568,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2976,1568,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3104,1568,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2720,1728,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2848,1728,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2976,1728,1,1 }));//no comment


                                                      //same area, not colorful trees

   gameObjects->obstacles.push_back(Obstacles({ 1152,352,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1280,352,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1408,352,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1152,512,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1280,512,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1408,512,1,1 }));//no comment

   gameObjects->obstacles.push_back(Obstacles({ 1408,1184,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1408,1056,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1408,928,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1408,800,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1408,640,1,1 }));//no comment


                                                     //left big trees (2)

   gameObjects->obstacles.push_back(Obstacles({ 672,1600,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 704,1568,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 864,1600,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 864,1568,1,1 }));//no comment

                                                     //pool 

   gameObjects->obstacles.push_back(Obstacles({ 1088,2048,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1120,2080,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1152,2080,1,1 }));//no comment

                                                      //small bushes around pool

   gameObjects->obstacles.push_back(Obstacles({ 992,1856,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1056,1856,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1120,1856,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1184,1856,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1248,1856,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1280,1856,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1312,1856,1,1 }));//no comment

                                                      //red thing with white lines ( or vice versa) in front of two people

   gameObjects->obstacles.push_back(Obstacles({ 1024,1568,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1056,1568,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1088,1600,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1024,1536,65,65 }));//no comment

                                                        //house near it

   gameObjects->obstacles.push_back(Obstacles({ 1120,1472,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1152,1472,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1184,1472,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1184,1504,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1152,1504,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1184,1568,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1152,1568,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1216,1472,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1216,1504,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1216,1536,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1216,1568,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1216,1600,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1184,1600,1,1 }));//no comment

                                                      //house next to it

   gameObjects->obstacles.push_back(Obstacles({ 1312,1472,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1344,1472,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1376,1472,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1376,1504,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1344,1504,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1312,1504,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1312,1536,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1344,1536,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1376,1536,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1408,1472,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1408,1504,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1408,1536,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1408,1568,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1376,1568,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1344,1568,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1312,1568,1,1 }));//no comment

                                                      //umbrella near pool

   gameObjects->obstacles.push_back(Obstacles({ 1344,1920,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1376,1920,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1408,1920,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1440,1920,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1440,1952,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1440,1984,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1408,1984,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1408,1952,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1376,1952,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1344,1952,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1344,1984,1,1 }));//no comment




                                                      //back coverage of the lighthouse a long rectangle

   gameObjects->obstacles.push_back(Obstacles({ 160,0,833,161 }));//no comment

                                                      //right sides of the lighthouse

   gameObjects->obstacles.push_back(Obstacles({ 512,512,513,65 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1056,576,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1056,544,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 736,448,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 224,448,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 256,480,1,1 }));//no comment

                                                    //reactor near the light house
                                                    //light house collisions
   gameObjects->obstacles.push_back(Obstacles({ 544,256,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 480,256,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 448,256,1,1 }));//no comment

                                                    //ATTENTION! when you add gate to light house, you might need to remove those two, maybe above three
   gameObjects->obstacles.push_back(Obstacles({ 480,288,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 448,288,1,1 }));//no comment

                                                    //lower pyramid 
   gameObjects->obstacles.push_back(Obstacles({ 2304,1152,65,129 }));//no comment

                                                         //upper pyramid
   gameObjects->obstacles.push_back(Obstacles({ 2304,864,65,97 }));//no comment

                                                       //thing near upper pyramid
   gameObjects->obstacles.push_back(Obstacles({ 2208,896,1,1 }));//no comment

                                                     //thing near lower pyramid
   gameObjects->obstacles.push_back(Obstacles({ 2208,1216,1,1 }));//no comment

                                                      //reactors  at the sides of the building ( around pyramid)

   gameObjects->obstacles.push_back(Obstacles({ 2112,1120,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1856,1120,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2112,1056,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1856,1056,1,1 }));//no comment

                                                      //things at the left  lower and upper
   gameObjects->obstacles.push_back(Obstacles({ 1792,1248,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1792,928,1,1 }));//no comment

                                                     //pyramid head building
   gameObjects->obstacles.push_back(Obstacles({ 2048,1056,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2016,1024,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1984,1024,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1952,1024,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1920,1024,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1920,1056,1,1 }));//no comment

                                                      //pyramd head building
                                                      //ATTENTION, those might need to be removed when gate added to the door
                                                      //it causes a weird bug (last test: emre)
   gameObjects->obstacles.push_back(Obstacles({ 2048,1120,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1920,1120,1,1 }));//no comment

                                                      // I dont remember but seems like home or tree

   gameObjects->obstacles.push_back(Obstacles({ 2048,1056,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2016,1024,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1984,1024,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1952,1024,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1920,1024,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1920,1056,1,1 }));//no comment

                                                      //tractor between pyramids

   gameObjects->obstacles.push_back(Obstacles({ 2560,1024,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2528,1024,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2496,1024,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2528,992,1,1 }));//no comment

                                                     // dead tree near reactor in cemetary

   gameObjects->obstacles.push_back(Obstacles({ 2944,192,1,1 }));//no comment

                                                     //reactor near dead three in cemetary

   gameObjects->obstacles.push_back(Obstacles({ 3104,224,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3072,192,1,1 }));//no comment

                                                     //building in the cemetary

   gameObjects->obstacles.push_back(Obstacles({ 3488,384,65,97 }));//no comment

                                                       //small house made of tree below cemetary

   gameObjects->obstacles.push_back(Obstacles({ 3648,1728,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3616,1664,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3584,1696,1,1 }));//no comment

                                                      //like aztec pyramid below cemetary
   gameObjects->obstacles.push_back(Obstacles({ 3296,1760,161,129 }));//no comment

                                                          //gameObjects->obstacles.push_back(Obstacles({ 3296,1728,161,161 }));//no comment
                                                          //gameObjects->obstacles.push_back(Obstacles({ 3296,1824,161,65 }));//no comment


                                                          //building like a church, in the left area 

                                                          //put the gate teleporter a little front or change the collision if gate does not work
   gameObjects->obstacles.push_back(Obstacles({ 800,1056,129,97 }));//no comment


                                                        //  gameObjects->obstacles.push_back(Obstacles({ 2176,864,33,65 }));//no comment
                                                        // gameObjects->obstacles.push_back(Obstacles({ 2304,1120,65,161 }));//no comment
                                                        /*
                                                        gameObjects->obstacles.push_back(Obstacles({ 1024,32,1,1 }));//no comment
                                                        gameObjects->obstacles.push_back(Obstacles({ 1024,64,1,1 }));//no comment
                                                        gameObjects->obstacles.push_back(Obstacles({ 1024,96,1,1 }));//no comment
                                                        gameObjects->obstacles.push_back(Obstacles({ 1024,128,1,1 }));//no comment
                                                        gameObjects->obstacles.push_back(Obstacles({ 1024,160,1,1 }));//no comment
                                                        gameObjects->obstacles.push_back(Obstacles({ 1024,192,1,1 }));//no comment
                                                        gameObjects->obstacles.push_back(Obstacles({ 1024,224,1,1 }));//no comment
                                                        gameObjects->obstacles.push_back(Obstacles({ 1024,256,1,1 }));//no comment
                                                        gameObjects->obstacles.push_back(Obstacles({ 1024,288,1,1 }));//no comment
                                                        gameObjects->obstacles.push_back(Obstacles({ 1024,320,1,1 }));//no comment
                                                        gameObjects->obstacles.push_back(Obstacles({ 1024,352,1,1 }));//no comment
                                                        gameObjects->obstacles.push_back(Obstacles({ 1024,384,1,1 }));//no comment
                                                        gameObjects->obstacles.push_back(Obstacles({ 1024,416,1,1 }));//no comment
                                                        gameObjects->obstacles.push_back(Obstacles({ 1024,448,1,1 }));//no comment
                                                        gameObjects->obstacles.push_back(Obstacles({ 1024,480,1,1 }));//no comment
                                                        gameObjects->obstacles.push_back(Obstacles({ 1024,512,1,1 }));//no comment
                                                        */
   gameObjects->obstacles.push_back(Obstacles({ 1056,0,1,513 }));//no comment

                                                     //left upper corner behind the trees ( right of lighthouse)

                                                     //gameObjects->obstacles.push_back(Obstacles({ 1088,0,737,1 }));//no comment

                                                     //colorful trees infront of the left upper corner

   gameObjects->obstacles.push_back(Obstacles({ 1152,64,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1280,64,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1408,64,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1536,64,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1664,64,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 1792,64,1,1 }));//no comment


                                                    //other colorful trees next to those , around cemetary

   gameObjects->obstacles.push_back(Obstacles({ 2080,64,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2208,64,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2336,64,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2464,64,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2592,64,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2720,64,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2464,192,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2592,192,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2720,192,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2848,192,1,1 }));//no comment


   gameObjects->obstacles.push_back(Obstacles({ 2752,480,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2880,480,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3008,480,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3136,480,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2624,576,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2752,576,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2880,576,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3008,576,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3136,576,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2624,672,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2752,672,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2880,672,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3008,672,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3136,672,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2880,768,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3008,768,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3136,768,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 2880,864,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3008,864,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3136,864,1,1 }));//no comment

                                                     //trees at the cemetary

   gameObjects->obstacles.push_back(Obstacles({ 2880,96,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3008,96,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3136,96,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3264,96,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3392,96,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3520,96,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3648,96,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3584,224,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3456,224,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3328,224,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3200,224,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3680,352,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3680,480,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3680,640,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3648,768,1,1 }));//no comment

                                                     //trees below cemetary, including big ones

   gameObjects->obstacles.push_back(Obstacles({ 3648,1504,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3648,1248,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3648,992,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3488,1024,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3488,1184,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3488,1344,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3232,1344,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3232,1184,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3232,1024,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3072,1152,1,1 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 3072,1408,1,1 }));//no comment

                                                      //lighthouse left sea coverage, right sea coverage

   gameObjects->obstacles.push_back(Obstacles({ 224,192,1,225 }));//no comment
   gameObjects->obstacles.push_back(Obstacles({ 736,192,1,225 }));//no comment

                                                      //gameObjects->obstacles.push_back(Obstacles({ 704,192,1,225 }));//no comment
}