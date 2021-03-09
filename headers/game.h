#ifndef GAME_H
#define GAME_H

#include <global.h>
#include <graphics.h>
#include <sprite.h>
#include <input.h>

class Graphics;

/*	Game class
 *	Holds information for main game loop
 */

class Game
{
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	Sprite _player;

public:
	Game();
	~Game();
};

#endif
