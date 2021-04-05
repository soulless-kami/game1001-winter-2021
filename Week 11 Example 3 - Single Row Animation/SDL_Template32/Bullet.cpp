#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(SDL_Renderer* renderer, int x, int y)
{
	pSpriteTex = IMG_LoadTexture(renderer, "bullet.png");

	SDL_QueryTexture(pSpriteTex, NULL, NULL, &src.w, &src.h);

	src.x = 0;
	src.y = 0;

	dY = y;

	dst.x = x;
	dst.y = y;
	dst.w = 5;
	dst.h = 5;
}

Bullet::~Bullet()
{
}

void Bullet::update(float deltaTime)
{
	dY -= velY * deltaTime;
	dst.y = dY;
}

void Bullet::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, pSpriteTex, &src, &dst);
}

void Bullet::cleanup()
{
}

bool Bullet::checkCollision(SDL_Rect r)
{
	return
		r.x < dst.x + dst.w &&
		r.x + r.w > dst.x &&
		r.y < dst.y + dst.h &&
		r.y + r.h > dst.y
		|| Bullet::outOfScreen();
		
}
