#include <rectangle.h>

Rectangle::Rectangle() {}
Rectangle::Rectangle(int x, int y, int width, int height)
	: _x(x),
	  _y(y),
	  _width(width),
	  _height(height){};

const int Rectangle::getCenterX() const { return this->_x + this->_width / 2; }
const int Rectangle::getCenterY() const { return this->_y + this->_height / 2; }

const int Rectangle::getLeft() const { return this->_x; }
const int Rectangle::getRight() const { return this->_x + this->_width; }
const int Rectangle::getTop() const { return this->_y; }
const int Rectangle::getBottom() const { return this->_y + this->_height; }

const int Rectangle::getWidth() const { return this->_width; }
const int Rectangle::getHeight() const { return this->_height; }

const int Rectangle::getSide(const sides::Side side) const
{
	if (side == sides::RIGHT)
		return this->getRight();
	else if (side == sides::LEFT)
		return this->getLeft();
	else if (side == sides::TOP)
		return this->getTop();
	else if (side == sides::BOTTOM)
		return this->getBottom();
	else
		return sides::NONE;
}

//	Checks if 2 Rectangles are colliding
const bool Rectangle::collidesWith(const Rectangle &other) const
{
	return (this->getRight() >= other.getLeft() &&
			this->getLeft() <= other.getRight() &&
			this->getTop() <= other.getBottom() &&
			this->getBottom() >= other.getTop());
}

bool Rectangle::isValidRectangle() const
{
	return (this->_x >= 0 &&
			this->_y >= 0 &&
			this->_width >= 0 &&
			this->_height >= 0);
}
