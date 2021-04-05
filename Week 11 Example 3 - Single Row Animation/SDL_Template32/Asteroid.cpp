#include "Asteroid.h"

SDL_Rect Asteroid::getRect()
{
    return dst;
}

Asteroid::Asteroid()
{
}

Asteroid::~Asteroid()
{
}

Asteroid::Asteroid(SDL_Renderer* renderer)
{
    pAsteroidTex = IMG_LoadTexture(renderer, "asteroid.png");
    SDL_QueryTexture(pAsteroidTex, NULL, NULL, &src.w, &src.h);


    src.x = 0;
    src.y = 0;


    dst.x = 240;
    dst.y = 160;
    dst.w = 160;
    dst.h = 160;

}

void Asteroid::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, pAsteroidTex, &src, &dst);
}

void Asteroid::cleanup()
{
}
