#include <shapes.h>

/*	Rectangle class
 *	Helps handle collision boxes
 */

Rectangle::Rectangle() {}
Rectangle::~Rectangle() {}
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

/*	Slope class
 *	Handles physics for slopes
 */

Slope::Slope() {}
Slope::Slope(Vector2 p1, Vector2 p2) : _p1(p1),
									   _p2(p2)
{
	if (this->_p2.x - this->_p1.x != 0)
		this->_slope = (fabs(this->_p2.y) - fabs(this->_p1.y)) / (fabs(this->_p2.x) - fabs(this->_p1.x));
}

const float Slope::getSlope() const { return this->_slope; }
const Vector2 Slope::getP1() const { return this->_p1; }
const Vector2 Slope::getP2() const { return this->_p2; }

//	Checks if the Slope were colliding with the Rectangle
const bool Slope::collidesWith(const Rectangle &other) const
{
	return (other.getRight() >= this->_p2.x &&
			other.getLeft() <= this->_p1.x &&
			other.getTop() <= this->_p2.y &&
			other.getBottom() >= this->_p1.y) ||

		   (other.getRight() >= this->_p1.x &&
			other.getLeft() <= this->_p2.x &&
			other.getTop() <= this->_p1.y &&
			other.getBottom() >= this->_p2.y) ||

		   (other.getLeft() <= this->_p1.x &&
			other.getRight() >= this->_p2.x &&
			other.getTop() <= this->_p1.y &&
			other.getBottom() >= this->_p2.y) ||

		   (other.getLeft() <= this->_p2.x &&
			other.getRight() >= this->_p1.x &&
			other.getTop() <= this->_p2.y &&
			other.getBottom() >= this->_p1.y);
}
