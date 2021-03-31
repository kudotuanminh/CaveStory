#include <animatedSprite.h>

/*	AnimatedSprite class
 *	Holds logic for animating sprites
 */

AnimatedSprite::AnimatedSprite() {}
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

//	Adds an animation to the map of animations for the sprite
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
	this->_animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rectangles));
	this->_offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

//	Resets all animations associated with this sprite
void AnimatedSprite::resetAnimations()
{
	this->_animations.clear();
	this->_offsets.clear();
}

//	Plays the animation provided if it's not already playing
void AnimatedSprite::playAnimation(std::string animation, bool once)
{
	this->_currentAnimationOnce = once;
	if (this->_currentAnimation != animation)
	{
		this->_currentAnimation = animation;
		this->_frameIndex = 0;
	}
}

//	Changes the visibility of the animated sprite
void AnimatedSprite::setVisible(bool visible) { this->_visible = visible; }

//	Stops the current animation
void AnimatedSprite::stopAnimation()
{
	this->_frameIndex = 0;
	this->animationDone(this->_currentAnimation);
}

//	Updates the animated sprite (w/ a timer)
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
			if (this->_currentAnimationOnce == true)
				this->setVisible(false);
			this->_frameIndex = 0;
			this->animationDone(this->_currentAnimation);
		}
	}
}

//	Draws the sprite to the screen
void AnimatedSprite::draw(Graphics &graphics, int x, int y)
{
	if (this->_visible)
	{
		SDL_Rect destinationRectangle;
		destinationRectangle.x = x + this->_offsets[this->_currentAnimation].x;
		destinationRectangle.y = y + this->_offsets[this->_currentAnimation].y;
		destinationRectangle.w = this->_sourceRect.w * global::SPRITE_SCALE;
		destinationRectangle.h = this->_sourceRect.h * global::SPRITE_SCALE;

		SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];
		graphics.blitSurface(
			this->_spriteSheet,
			&sourceRect,
			&destinationRectangle);
	}
}

/*

//	Required function to sets up all animations for a sprite
void AnimatedSprite::setupAnimations()
{
}

//	Logic that happens when an animation ends
void AnimatedSprite::animationDone(std::string currentAnimation)
{
}

*/
