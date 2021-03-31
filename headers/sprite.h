#ifndef SPRITE_H
#define SPRITE_H

#include <global.h>
#include <graphics.h>
#include <rectangle.h>

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

	virtual ~Sprite();
	virtual void update();

	void draw(Graphics &graphic, int x, int y);

	const Rectangle getBoundingBox() const;
	const sides::Side getCollisionSide(Rectangle &other) const;
};

#endif
