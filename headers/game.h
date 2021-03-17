#ifndef GAME_H
#define GAME_H

#include <global.h>
#include <graphics.h>
#include <player.h>
#include <input.h>

class Game
{
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	Player _player;

public:
	Game();
	~Game();
};

#endif
