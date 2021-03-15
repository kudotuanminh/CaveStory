#include <sprite.h>

/*	Sprite class
 *	Holds information for individual sprites
 */

Sprite::Sprite() {}
Sprite::~Sprite() {}
Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY) : _x(posX), _y(posY)
{
	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = width;
	this->_sourceRect.h = height;

	//SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	if (this->_spriteSheet == NULL)
		std::cout << "\nError: Unable to load image\n";
}

void Sprite::draw(Graphics &graphics, int x, int y)
{
	SDL_Rect destinationRectangle = {x, y, static_cast<int>(global::SPRITE_SCALE * this->_sourceRect.w), static_cast<int>(global::SPRITE_SCALE * this->_sourceRect.h)};
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}

void Sprite::update()
{
}
