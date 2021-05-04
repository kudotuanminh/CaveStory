#ifndef GAME_H
#define GAME_H

#include <global.h>
#include <level.h>
#include <HUD.h>

class Game
{
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	Player _player;

	Level _level;

	HUD _hud;

public:
	Game();
	~Game();
};

#endif
