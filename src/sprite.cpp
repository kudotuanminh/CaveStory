#include <sprite.h>

/*	Sprite class
 *	Holds information for individual sprites
 */

Sprite::Sprite() {}
Sprite::~Sprite() {}
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

void Sprite::update()
{
	this->_boundingBox = Rectangle(
		this->_x,
		this->_y,
		global::SPRITE_SCALE * this->_sourceRect.w,
		global::SPRITE_SCALE * this->_sourceRect.h);
}

const Rectangle Sprite::getBoundingBox() const { return this->_boundingBox; }

//	Determine the side which the collision happens
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
