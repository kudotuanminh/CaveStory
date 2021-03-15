#ifndef GLOBAL_H
#define GLOBAL_H

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

namespace global
{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	const float SPRITE_SCALE = 2.0f;
}

struct Vector2
{
	int x, y;
	Vector2() : x(0), y(0) {}
	Vector2(int _x, int _y) : x(_x), y(_y) {}
	Vector2 zero()
	{
		return Vector2(0, 0);
	}
};

#endif
