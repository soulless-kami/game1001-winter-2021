#pragma once
#include <SDL_image.h>
#include <math.h>

// Sprite class which contains a texture, position, velocity, size, and functions for drawing it.

class Sprite
{
	SDL_Texture* pSpriteTex = nullptr;
	SDL_Rect src;

public:
	SDL_Rect dst;

	// velocity (maybe not necessary for every sprite)
	float velX = 0;
	float velY = 0;

	// constructors -- these are used when initializing an object
	Sprite();
	Sprite(SDL_Renderer* renderer, const char* filename, 
		int w, int h);
	Sprite(SDL_Renderer* renderer, const char* filename, 
		int srcX, int srcY, int srcW, int srcH, 
		int dstX, int dstY, int dstW, int dstH);

	// destructor -- used when the object is to be removed from memory
	~Sprite();

	void draw(SDL_Renderer* renderer);

	void cleanup();


	float speed = 5.0f;
};