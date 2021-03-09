#ifndef GAME_H
#define GAME_H

#include <global.h>

class Graphics;

/*	Game class
 *	Holds information for main game loop
 */

class Game
{
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(double elapsedTime);

public:
	Game();
	~Game();
};

#endif
