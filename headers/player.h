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
	bool _grounded, _lookingUp, _lookingDown;
	int _maxHealth, _currentHealth;

public:
	Player();
	Player(Graphics &graphics, Vector2 spawnPoint);
	~Player();

	const float getX() const;
	const float getY() const;
	const int getMaxHealth() const;
	const int getCurrentHealth() const;

	virtual void setupAnimations();
	virtual void animationDone(std::string currentAnimation);

	void draw(Graphics &graphics);
	void update(float elapsedTime);

	void moveLeft();
	void moveRight();
	void stopMoving();

	void lookUp();
	void stopLookingUp();
	void lookDown();
	void stopLookingDown();

	void jump();

	void handleTileCollisions(std::vector<Rectangle> &others);
	void handleSlopeCollisions(std::vector<Slope> &others);
};

#endif
