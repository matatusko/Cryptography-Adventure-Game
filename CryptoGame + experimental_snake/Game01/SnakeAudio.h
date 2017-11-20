#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_mixer.h>

class SnakeAudio
{
	friend class SnakeGame;

	SnakeAudio();

private:

    Mix_Chunk *one = NULL;
	Mix_Chunk *two = NULL;
	Mix_Chunk *three = NULL;

	void loadAudio();
	void playOne();
	void playTwo();
	void playThree();
	void destroyAudio();
};

SnakeAudio::SnakeAudio()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
    
	loadAudio();
}

void SnakeAudio::loadAudio()
{
	one = Mix_LoadWAV("master.wav");
	if (one == NULL) { printf("no scratch"); }

	two = Mix_LoadWAV("fx.wav");
	three = Mix_LoadWAV("fx.wav");
}

void SnakeAudio::playOne()
{
	Mix_PlayChannel(-1, one, 0);
}

void SnakeAudio::playTwo()
{
	Mix_PlayChannel(-1, two, 0);
}

void SnakeAudio::playThree()
{
	Mix_PlayChannel(-1, three, 0);
}

void SnakeAudio::destroyAudio()
{
	Mix_FreeChunk(one);
	Mix_FreeChunk(two);
	Mix_FreeChunk(three);
	Mix_Quit();
}

