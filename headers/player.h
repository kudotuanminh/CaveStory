#ifndef PLAYER_H
#define PLAYER_H

#include <global.h>
#include <animatedSprite.h>

class Player : public AnimatedSprite
{
private:
	float _dx, _dy;
	Direction _facing;

public:
	Player();
	Player(Graphics &graphics, float x, float y);

	void draw(Graphics &graphics);
	void update(float elapsedTime);

	void moveLeft();
	void moveRight();
	void stopMoving();

	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();
};

#endif
