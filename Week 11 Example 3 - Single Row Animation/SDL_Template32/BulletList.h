#include "Bullet.h"
#include "Asteroid.h"
#include <vector>


class BulletList {
	std::vector<Bullet> bulletArray;
	int bulletLimit = 1;

public:

	BulletList();
	BulletList(int limitOnBullets);
	~BulletList();

	void AddBullet(SDL_Renderer* renderer, int x, int y);
	void UpdateBullets(SDL_Renderer* renderer, float deltaTime, Asteroid obstacle);
};