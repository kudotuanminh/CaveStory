#ifndef HUD_H
#define HUD_H

#include <global.h>
#include <sprite.h>
#include <player.h>

class HUD
{
private:
	Player _player;

	Sprite _healthBarSprite, _healthNumber1;

public:
	HUD();
	HUD(Graphics &graphics, Player &player);
	~HUD();

	void update(int elapsedTime);
	void draw(Graphics &graphics);
};

#endif
