#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <global.h>

class Rectangle
{
private:
	int _x, _y, _width, _height;

public:
	Rectangle();
	Rectangle(int x, int y, int width, int height);

	const int getCenterX() const;
	const int getCenterY() const;

	const int getLeft() const;
	const int getRight() const;
	const int getTop() const;
	const int getBottom() const;

	const int getWidth() const;
	const int getHeight() const;

	const int getSide(const sides::Side side) const;

	const bool collidesWith(const Rectangle &other) const;

	bool isValidRectangle() const;
};

#endif
