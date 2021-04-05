#pragma once
#include <SDL_image.h>

class Asteroid
{
	SDL_Texture* pAsteroidTex = nullptr;
	SDL_Rect src;
	SDL_Rect dst;

public:

	SDL_Rect getRect();

	Asteroid();
	~Asteroid();
	Asteroid(SDL_Renderer* renderer);


	void draw(SDL_Renderer* renderer);
	void cleanup();

};

