#ifndef HUD_H
#define HUD_H

#include <global.h>
#include <sprite.h>
#include <player.h>

class HUD
{
private:
	Player _player;

	//	HP
	Sprite
		_healthBarSprite,
		_healthNumber1,
		_currentHealthBar;

	// EXP
	Sprite
		_lvWord,
		_lvNumber,
		_expBar;

	//	Weapon
	Sprite
		_slash,
		_dashes;

public:
	HUD();
	HUD(Graphics &graphics, Player &player);
	~HUD();

	void update(int elapsedTime);
	void draw(Graphics &graphics);
};

#endif
