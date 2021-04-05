#include "BulletList.h"

BulletList::BulletList(int limitOnBullets)
{
	BulletList::bulletLimit = limitOnBullets;
}


BulletList::~BulletList() {}
BulletList::BulletList() {}

void BulletList::AddBullet(SDL_Renderer* renderer, int x, int y)
{
	if(bulletArray.size() < BulletList::bulletLimit)
		bulletArray.emplace_back(Bullet(renderer, x, y));
}

void BulletList::UpdateBullets(SDL_Renderer* renderer, float deltaTime, Asteroid obstacle)
{
	for (auto it = bulletArray.begin(); it != bulletArray.end();) {
		it->update(deltaTime);
		if (it->checkCollision(obstacle.getRect()))
		{
			it = bulletArray.erase(it);
		}
		else
		{
			it->draw(renderer);
			++it;
		}
	}
}