#ifndef PLAYER_H
#define PLAYER_H

#include <global.h>
#include <animatedSprite.h>

class Player : public AnimatedSprite
{
private:
	float _dx, _dy;
	Direction _facing;
	bool _grounded;

public:
	Player();
	Player(Graphics &graphics, Vector2 spawnPoint);

	void draw(Graphics &graphics);
	void update(float elapsedTime);

	void moveLeft();
	void moveRight();
	void stopMoving();

	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();

	void handleTileCollisions(std::vector<Rectangle> &others);

	const float getX() const;
	const float getY() const;
};

#endif
