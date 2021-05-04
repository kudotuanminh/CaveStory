#include <player.h>

/*	Player class
 *	Render graphics and controls player's character
 */

Player::Player() {}
Player::Player(Graphics &graphics, Vector2 spawnPoint)
	: AnimatedSprite(graphics,
					 "content/sprites/MyChar.png",
					 0, 0,
					 16, 16,
					 spawnPoint.x, spawnPoint.y,
					 100),
	  _dx(0),
	  _dy(0),
	  _facing(RIGHT),
	  _grounded(false),
	  _lookingUp(false),
	  _lookingDown(false),
	  _maxHealth(3),
	  _currentHealth(3)
{
	graphics.loadImage("content/sprites/MyChar.png");

	this->setupAnimations();
	this->playAnimation("RunRight");
}
Player::~Player() {}

const float Player::getX() const { return this->_x; }
const float Player::getY() const { return this->_y; }
const int Player::getMaxHealth() const { return this->_maxHealth; }
const int Player::getCurrentHealth() const { return this->_currentHealth; }

void Player::setupAnimations()
{
	this->addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 3, 0, "IdleLeftUp", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 3, 16, "IdleRightUp", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 3, 0, "RunLeftUp", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 3, 16, "RunRightUp", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 6, 0, "LookDownLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 6, 16, "LookDownRight", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 7, 0, "LookBackwardsLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 7, 16, "LookBackwardsRight", 16, 16, Vector2(0, 0));
}

void Player::animationDone(std::string currentAnimation) {}

void Player::draw(Graphics &graphics) { AnimatedSprite::draw(graphics, this->_x, this->_y); }

void Player::update(float elapsedTime)
{
	//	apply gravity
	if (this->_dy <= player_constants::GRAVITY_CAP)
		this->_dy += player_constants::GRAVITY * elapsedTime;
	//	move by dx
	this->_x += this->_dx * elapsedTime;
	//	move by dy
	this->_y += this->_dy * elapsedTime;

	AnimatedSprite::update(elapsedTime);
}

void Player::moveLeft()
{
	if (this->_lookingDown && this->_grounded)
		return;
	this->_dx = -player_constants::WALK_SPEED;
	if (!this->_lookingUp)
		this->playAnimation("RunLeft");
	this->_facing = LEFT;
}

void Player::moveRight()
{

	if (this->_lookingDown && this->_grounded)
		return;
	this->_dx = player_constants::WALK_SPEED;
	if (!this->_lookingUp)
		this->playAnimation("RunRight");
	this->_facing = RIGHT;
}

void Player::stopMoving()
{
	this->_dx = 0.0f;
	if (!this->_lookingUp && !this->_lookingDown)
		this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::lookUp()
{
	this->_lookingUp = true;
	if (this->_dx == 0)
		this->playAnimation(this->_facing == RIGHT ? "IdleRightUp" : "IdleLeftUp");
	else
		this->playAnimation(this->_facing == RIGHT ? "RunRightUp" : "RunLeftUp");
}

void Player::stopLookingUp() { this->_lookingUp = false; }

void Player::lookDown()
{
	this->_lookingDown = true;
	if (this->_grounded)
		this->playAnimation(this->_facing == RIGHT ? "LookBackwardsRight" : "LookBackwardsLeft");
	else
		this->playAnimation(this->_facing == RIGHT ? "LookDownRight" : "LookDownLeft");
}

void Player::stopLookingDown() { this->_lookingDown = false; }

void Player::jump()
{
	if (this->_grounded)
	{
		this->_dy = -player_constants::JUMP_SPEED;
		this->_grounded = false;
	}
}

void Player::handleTileCollisions(std::vector<Rectangle> &others)
{
	//	Figure out which side the collision happens on and move the player accordingly
	for (int i = 0; i < others.size(); i++)
	{
		sides::Side collisionSide = Sprite::getCollisionSide(others[i]);
		if (collisionSide != sides::NONE)
			switch (collisionSide)
			{
			case sides::TOP:
				this->_dy = 0;
				this->_y = others[i].getBottom() + 1;
				if (this->_grounded)
				{
					this->_dx = 0;
					this->_x -= this->_facing == RIGHT ? 1.0f : -1.0f;
				}
				break;
			case sides::BOTTOM:
				this->_y = others[i].getTop() - this->_boundingBox.getHeight() - 1;
				this->_dy = 0;
				this->_grounded = true;
				break;
			case sides::LEFT:
				this->_x = others[i].getRight() + 1;
				break;
			case sides::RIGHT:
				this->_x = others[i].getLeft() - this->_boundingBox.getWidth() - 1;
				break;
			}
	}
}

void Player::handleSlopeCollisions(std::vector<Slope> &others)
{
	for (int i = 0; i < others.size(); i++)
	{
		//	Calculate where on the slope the player's bottom center is touching and use 'y = mx + b' to figure out the y position to place him at
		//	First calculate 'b' (slope intercept) using one of the points (b = y - mx)
		int b = (others[i].getP1().y - (others[i].getSlope() * fabs(others[i].getP1().x)));
		//	afterward get player's center X
		int centerX = this->_boundingBox.getCenterX();
		//	then find Y
		int newY = (others[i].getSlope() * centerX) + b - 8; //	8 is temporary fix
		//	Reposition the player to the correct Y
		if (this->_grounded)
		{
			this->_y = newY - this->_boundingBox.getHeight();
			this->_grounded = true;
		}
	}
}
