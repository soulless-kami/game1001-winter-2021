#include "Ship.h"
#include <iostream>

//constructor
Ship::Ship()
{
}

//constructor
Ship::Ship(SDL_Renderer* renderer, const char* filename,
	int w, int h)
{
	pSpriteTex = IMG_LoadTexture(renderer, filename);

	SDL_QueryTexture(pSpriteTex, NULL, NULL, &src.w, &src.h);

	src.x = 0;
	src.y = 0;

	dX = 0;
	dY = 0;

	dst.x = 0;
	dst.y = 0;
	dst.w = w;
	dst.h = h;
}

//constructor
Ship::Ship(SDL_Renderer* renderer, const char* filename,
	int srcX, int srcY, int srcW, int srcH,
	int dstX, int dstY, int dstW, int dstH)
{
	pSpriteTex = IMG_LoadTexture(renderer, filename);

	SDL_QueryTexture(pSpriteTex, NULL, NULL, &src.w, &src.h);

	src.x = srcX;
	src.y = srcY;
	src.w = srcW;
	src.h = srcH;


	dX = dstX;
	dY = dstY;

	dst.x = dstX;
	dst.y = dstY;
	dst.w = dstW;
	dst.h = dstH;
}


//destructor
Ship::~Ship()
{
}


void Ship::cleanup()
{
	SDL_DestroyTexture(pSpriteTex);
}

void Ship::setPosition(int x, int y)
{
	dst.x = x;
	dst.y = y;
}

void Ship::moveBy(float x, float y)
{
	dX += x * speedx;
	dY += y * speedy;
	setPosition(dX, dY);

	if (dst.x < 0 || dst.x > 567)
	{
		speedx = -50.0f;

		if (dst.x < 0) dst.x += x + 3.5f;

		else if (dst.x > 567) dst.x += x - 3.5f;
	}
	else if (dst.x > 0 || dst.x < 567) speedx = 4.0f;

	if (dst.y < 0 || dst.y>433)
	{
		speedy = -50.0;
		if (dst.y < 0) dst.y += y + 3.5f;

		else if (dst.y > 433) dst.y += y - 3.5f;
	}
	else if (dst.y > 0 || dst.y < 433) speedy = 4.0f;

}

void Ship::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, pSpriteTex, &src, &dst);
}
