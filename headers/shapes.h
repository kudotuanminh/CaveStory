#ifndef SHAPES_H
#define SHAPES_H

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

class Slope
{
private:
	Vector2 _p1, _p2;
	float _slope;

public:
	Slope();
	Slope(Vector2 p1, Vector2 p2);

	const float getSlope() const;
	const Vector2 getP1() const;
	const Vector2 getP2() const;

	const bool collidesWith(const Rectangle &other) const;
};

#endif
