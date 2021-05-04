#ifndef GAME_H
#define GAME_H

#include <global.h>
#include <level.h>
#include <HUD.h>

class Game
{
private:
	Player _player;

	Level _level;

	HUD _hud;

	void gameLoop();
	void draw(Graphics &graphics);
	void update(float elapsedTime);

public:
	Game();
	~Game();
};

#endif
