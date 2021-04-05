#ifndef __GAME__
#define __GAME__

#include "SDL.h"
#include "Sprite.h"
#include "Ship.h"
#include "BulletList.h"
#include "Asteroid.h"
#include "Background.h"
#include "Smoke.h"

class Game
{

public:

	Game();
	~Game();

	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	//we do one time preparation stuff here
	void prepare();

	//these four functions make our game loop
	void handleEvents();
	void update();
	void render();
	void waitForNextFrame();

	//another single call function which runs just before the game is closed
	void cleanup();

	//function to aaccess the running variable
	bool running() { return m_bRunning; }


	


private:

	Ship ship;
	Background background;
	BulletList bullets;
	Asteroid obstacle;
	Smoke smoke;




	/* 
	A pointer points to an object and is denoted by a "*" in declaration. 
	So m_pWindow is a Pointer which *points* to an object of type SDL_Window
	*/
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	
	bool m_bRunning;

	bool animateSmoke = false;

	//For framerate
	int targetFramerate = 30;
	int frameDelayMs = 1000 / targetFramerate;

	Uint32 currentFrameEndTime;
	Uint32 currentFrameStartTime;
	Uint32 timeSinceLastFrame;

	//for gameplay
	float deltaTime;

	//Keep gameTime in seconds
	float gameTime = 0;
};


#endif /* defined (__Game__) */

