#include <sprite.h>

/*	Sprite class
 *	Holds information for individual sprites
 */

Sprite::Sprite() {}
Sprite::Sprite(
	Graphics &graphics,
	const std::string &filePath,
	int sourceX, int sourceY,
	int width, int height,
	float posX, float posY) : _x(posX),
							  _y(posY)
{
	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = width;
	this->_sourceRect.h = height;

	this->_spriteSheet = SDL_CreateTextureFromSurface(
		graphics.getRenderer(),
		graphics.loadImage(filePath));
	if (this->_spriteSheet == NULL)
		std::cerr << "\nError: Unable to load image\n";

	this->_boundingBox = Rectangle(
		this->_x,
		this->_y,
		global::SPRITE_SCALE * width,
		global::SPRITE_SCALE * height);
}

void Sprite::update()
{
	this->_boundingBox = Rectangle(
		this->_x,
		this->_y,
		global::SPRITE_SCALE * this->_sourceRect.w,
		global::SPRITE_SCALE * this->_sourceRect.h);
}

void Sprite::draw(Graphics &graphics, int x, int y)
{
	SDL_Rect destinationRectangle = {
		x,
		y,
		global::SPRITE_SCALE * this->_sourceRect.w,
		global::SPRITE_SCALE * this->_sourceRect.h};
	graphics.blitSurface(
		this->_spriteSheet,
		&this->_sourceRect,
		&destinationRectangle);
}

const Rectangle Sprite::getBoundingBox() const { return this->_boundingBox; }

const sides::Side Sprite::getCollisionSide(Rectangle &other) const
{
	int amountRight = this->getBoundingBox().getRight() - other.getLeft(),
		amountLeft = other.getRight() - this->getBoundingBox().getLeft(),
		amountTop = other.getBottom() - this->getBoundingBox().getTop(),
		amountBottom = this->getBoundingBox().getBottom() - other.getTop();

	int vals[4] = {abs(amountRight), abs(amountLeft), abs(amountTop), abs(amountBottom)};
	int min = *std::min_element(vals, vals + 4);
	if (min == abs(amountRight))
		return sides::RIGHT;
	else if (min == abs(amountLeft))
		return sides::LEFT;
	else if (min == abs(amountTop))
		return sides::TOP;
	else if (min == abs(amountBottom))
		return sides::BOTTOM;
	else
		return sides::NONE;
}

/*	AnimatedSprite class
 *	Holds logic for animating sprites
 */

AnimatedSprite::AnimatedSprite() {}
AnimatedSprite::~AnimatedSprite() {}
AnimatedSprite::AnimatedSprite(
	Graphics &graphics,
	const std::string &filePath,
	int sourceX, int sourceY,
	int width, int height,
	float posX, float posY,
	float timeToUpdate) : Sprite(graphics,
								 filePath,
								 sourceX, sourceY,
								 width, height,
								 posX, posY),
						  _frameIndex(0),
						  _timeToUpdate(timeToUpdate),
						  _visible(true),
						  _currentAnimationOnce(false),
						  _currentAnimation("") {}

void AnimatedSprite::update(int elapsedTime)
{
	Sprite::update();

	this->_timeElapsed += elapsedTime;
	if (this->_timeElapsed > this->_timeToUpdate)
	{
		this->_timeElapsed -= this->_timeToUpdate;
		if (this->_frameIndex < this->_animations[this->_currentAnimation].size() - 1)
			this->_frameIndex++;
		else
		{
			if (this->_currentAnimationOnce)
				this->setVisible(false);
			this->stopAnimation();
		}
	}
}

void AnimatedSprite::draw(Graphics &graphics, int x, int y)
{
	if (this->_visible)
	{
		SDL_Rect destinationRectangle;
		destinationRectangle.x = x + this->_offsets[this->_currentAnimation].x;
		destinationRectangle.y = y + this->_offsets[this->_currentAnimation].y;
		destinationRectangle.w = global::SPRITE_SCALE * this->_sourceRect.w;
		destinationRectangle.h = global::SPRITE_SCALE * this->_sourceRect.h;

		SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];
		graphics.blitSurface(
			this->_spriteSheet,
			&sourceRect,
			&destinationRectangle);
	}
}

void AnimatedSprite::addAnimation(
	int frames,
	int x, int y,
	std::string name,
	int width, int height,
	Vector2 offset)
{
	std::vector<SDL_Rect> rectangles;
	for (int i = 0; i < frames; i++)
	{
		SDL_Rect newRect = {(i + x) * width, y, width, height};
		rectangles.push_back(newRect);
	}
	this->_animations.insert(std::pair<std::string,
									   std::vector<SDL_Rect>>(name, rectangles));
	this->_offsets.insert(std::pair<std::string,
									Vector2>(name, offset));
}

void AnimatedSprite::resetAnimations()
{
	this->_animations.clear();
	this->_offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once)
{
	this->_currentAnimationOnce = once;
	if (this->_currentAnimation != animation)
	{
		this->_currentAnimation = animation;
		this->_frameIndex = 0;
	}
}

void AnimatedSprite::setVisible(bool visible) { this->_visible = visible; }

void AnimatedSprite::stopAnimation()
{
	this->_frameIndex = 0;
	this->animationDone(this->_currentAnimation);
}
