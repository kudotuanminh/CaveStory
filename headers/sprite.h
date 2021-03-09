#ifndef SPRITE_H
#define SPRITE_H

#include <global.h>
#include <graphics.h>

/*	Input class
 *	Holds information for individual sprites
 */

class Sprite
{
private:
	SDL_Rect _sourceRect;
	SDL_Texture *_spriteSheet;

	float _x, _y;

public:
	Sprite();
	Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY);

	virtual ~Sprite();
	virtual void update();

	void draw(Graphics &graphic, int x, int y);
};

#endif
