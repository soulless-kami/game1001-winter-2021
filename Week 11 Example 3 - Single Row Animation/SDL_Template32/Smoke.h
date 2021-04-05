#pragma once
#include <SDL_image.h>

class Smoke
{
	SDL_Texture* pSpriteTex = nullptr;
	SDL_Rect src;
	SDL_Rect dst;
	SDL_Renderer* renderer;

	int displayFrame = 0;
	int frameCount = 24;

	int frameWidth = 32;
	int frameHeight = 32;
public:




	// constructors -- these are used when initializing an object
	Smoke();
	Smoke(SDL_Renderer* renderer, int posX, int posY);

	// destructor -- used when the object is to be removed from memory
	~Smoke();

	bool animate();
	void cleanup();
};

