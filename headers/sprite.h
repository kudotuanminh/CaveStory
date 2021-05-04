#ifndef SPRITE_H
#define SPRITE_H

#include <global.h>
#include <graphics.h>
#include <shapes.h>

class Sprite
{
private:
protected:
	float _x, _y;

	SDL_Rect _sourceRect;
	SDL_Texture *_spriteSheet;

	Rectangle _boundingBox;

public:
	Sprite();
	Sprite(
		Graphics &graphics,
		const std::string &filePath,
		int sourceX, int sourceY,
		int width, int height,
		float posX, float posY);
	~Sprite();

	const float getX() const;
	const float getY() const;
	const Rectangle getBoundingBox() const;
	const sides::Side getCollisionSide(Rectangle &other) const;

	virtual void update();
	void draw(Graphics &graphic, int x, int y);

	void setSourceRectX(int value);
	void setSourceRectY(int value);
	void setSourceRectW(int value);
	void setSourceRectH(int value);
};

class AnimatedSprite : public Sprite
{
private:
	std::map<std::string, std::vector<SDL_Rect>> _animations;
	std::map<std::string, Vector2> _offsets;

	int _frameIndex;
	double _timeElapsed;
	bool _visible;

protected:
	double _timeToUpdate;
	bool _currentAnimationOnce;
	std::string _currentAnimation;

	void addAnimation(
		int frames,
		int x, int y,
		std::string name,
		int width, int height,
		Vector2 offset);
	void resetAnimations();
	void stopAnimation();
	void setVisible(bool visible);

	virtual void setupAnimations() = 0;
	virtual void animationDone(std::string currentAnimation) = 0;

public:
	AnimatedSprite();
	AnimatedSprite(
		Graphics &graphics,
		const std::string &filePath,
		int sourceX, int sourceY,
		int width, int height,
		float posX, float posY,
		float timeToUpdate);
	~AnimatedSprite();

	void update(int elapsedTime);
	void draw(Graphics &graphics, int x, int y);

	void playAnimation(std::string animation, bool once = false);
};

#endif
