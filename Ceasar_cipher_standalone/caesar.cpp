/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//Button constants
const int BUTTON_WIDTH = 88;
const int BUTTON_HEIGHT = 88;
const int TOTAL_BUTTONS = 21;


enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 2,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = BUTTON_SPRITE_MOUSE_OUT+1*7,
	BUTTON_SPRITE_MOUSE_DOWN = BUTTON_SPRITE_MOUSE_OUT+2*7,
	//BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 7
};

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif
		
		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//The mouse button
class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y , int current_sprite);

		//Handles mouse event
		void handleEvent( SDL_Event* e );
	
		//Shows button sprite
		void render();

		//Returns pressed state
		bool isPressed();

		//Resets press state
		void resetPress();

	private:
		//Top left position
		SDL_Point mPosition;

		//Currently used global sprite
		int mCurrentSprite;
   		int mLastSprite;
   		int hoversprite;
		int presssprite; 

		bool pressed;
};

bool LButton::isPressed() {
	return pressed;
}

void LButton::resetPress() {
	pressed = false;
}

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

// background image
LTexture ada_background;
//Overlay images
LTexture start_state;
LTexture state_3;
LTexture state_4;
LTexture state_5;
LTexture state_6;
LTexture state_7;

//Mouse button sprites
SDL_Rect gSpriteClips[ TOTAL_BUTTONS ];
LTexture gButtonSpriteSheetTexture;

//Buttons objects
LButton gButtons[ TOTAL_BUTTONS ]; 

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	
	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;
	pressed = false;
}

void LButton::setPosition( int x, int y , int current_sprite)
{
	mPosition.x = x;
	mPosition.y = y;

	mCurrentSprite = current_sprite;
   	mLastSprite = current_sprite;
	hoversprite = current_sprite + 7;
	presssprite = current_sprite + 14;
}

void LButton::handleEvent( SDL_Event* e )
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + BUTTON_WIDTH )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + BUTTON_HEIGHT )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			mCurrentSprite = mLastSprite;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
				mCurrentSprite = hoversprite;
				break;
			
				case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = presssprite;
				mLastSprite = presssprite;
				pressed = true;
				break;
				
				// case SDL_MOUSEBUTTONUP:
				// mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				// break;
			}
		}
	}
}
	
void LButton::render()
{
	//Show current button sprite
	gButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ] );
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//load background
	if (!ada_background.loadFromFile("ada_screen.png")) {
		std::cout << "Failed to load the ada_screen texture" << std::endl;
		success = false;
	}
	//Load wheel states
	if (!start_state.loadFromFile("start_state.png")) {
		std::cout << "Failed to load the start_state texture" << std::endl;
		success = false;
	}
	if (!state_3.loadFromFile("state_3.png")) {
		std::cout << "Failed to load the state_3 texture" << std::endl;
		success = false;
	}
	if (!state_4.loadFromFile("state_4.png")) {
		std::cout << "Failed to load the state_4 texture" << std::endl;
		success = false;
	}
	if (!state_5.loadFromFile("state_5.png")) {
		std::cout << "Failed to load the state_5 texture" << std::endl;
		success = false;
	}
	if (!state_6.loadFromFile("state_6.png")) {
		std::cout << "Failed to load the state_6 texture" << std::endl;
		success = false;
	}
	if (!state_7.loadFromFile("state_7.png")) {
		std::cout << "Failed to load the state_7 texture" << std::endl;
		success = false;
	}
	
	//Load sprites
	if( !gButtonSpriteSheetTexture.loadFromFile( "c_buttons.png" ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else
	{	
      	for (int y = 0, curr = 0; y < 3; y++) {
			for (int x = 0; x < 7; x++, curr++)
			{
				std::cout << "curr = " << curr << std::endl;
				gSpriteClips[curr].x = x*BUTTON_WIDTH;
				gSpriteClips[curr].y = y*BUTTON_HEIGHT;
				gSpriteClips[curr].w = BUTTON_WIDTH;
				gSpriteClips[curr].h = BUTTON_HEIGHT;
			}
			std::cout << "endx" << curr << std::endl;
			std::cout << "y" << y << std::endl;
      	}
			gButtons[0].setPosition(316, 448, 0);
			gButtons[1].setPosition(272, 360, 1);
			gButtons[2].setPosition(360, 360, 2);
			gButtons[3].setPosition(228, 272, 3);
			gButtons[4].setPosition(316, 272, 4);
			gButtons[5].setPosition(404, 272, 5);
			gButtons[6].setPosition(316, 184, 6);
	}

	return success;
}

void close()
{
	//Free loaded images
	gButtonSpriteSheetTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					
					//Handle button events
					for( int i = 0; i < TOTAL_BUTTONS; ++i )
					{
						gButtons[ i ].handleEvent( &e );
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				//render background
				ada_background.render(0,0);
				//render start start_state
				start_state.render(0,0);

				//Render buttons
				for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i )
				{
					gButtons[ i ].render();
				}

				
				if (gButtons[2].isPressed()) {
					state_4.render(0,0);
				}
				if (gButtons[3].isPressed()) {
					state_5.render(0,0);
				}
				
				if (gButtons[5].isPressed()) {
					state_7.render(0,0);
				}

				if (gButtons[1].isPressed()) {
					if (gButtons[5].isPressed()) {
						state_3.render(0,0);
						state_7.render(0,0);
						
					}
					else if (gButtons[3].isPressed()) {
						state_3.render(0,0);
						state_5.render(0,0);
						
					}
					 else {state_3.render(0,0);}
				}

				if (gButtons[4].isPressed()) {
					state_6.render(0,0);
				}
				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}