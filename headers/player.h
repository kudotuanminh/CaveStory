#ifndef PLAYER_H
#define PLAYER_H

#include <global.h>
#include <sprite.h>

namespace player_constants
{
	const float WALK_SPEED = 0.2f;
	const float JUMP_SPEED = 0.7f;

	const float GRAVITY = 0.002f;
	const float GRAVITY_CAP = 0.8f;
}

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
	void jump();

	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();

	void handleTileCollisions(std::vector<Rectangle> &others);
	void handleSlopeCollisions(std::vector<Slope> &others);

	const float getX() const;
	const float getY() const;
};

#endif
