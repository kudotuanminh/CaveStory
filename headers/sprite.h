#ifndef SPRITE_H
#define SPRITE_H

#include <global.h>
#include <graphics.h>

class Sprite
{
private:
protected:
	float _x, _y;

	SDL_Rect _sourceRect;
	SDL_Texture *_spriteSheet;

public:
	Sprite();
	Sprite(Graphics &graphics,
		   const std::string &filePath,
		   int sourceX, int sourceY,
		   int width, int height,
		   float posX, float posY);

	virtual ~Sprite();
	virtual void update();

	void draw(Graphics &graphic, int x, int y);
};

#endif
