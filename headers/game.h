#ifndef GAME_H
#define GAME_H

#include <global.h>
#include <player.h>
#include <level.h>

class Game
{
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	Player _player;

	Level _level;

public:
	Game();
	~Game();
};

#endif
