#ifndef GLOBAL_H
#define GLOBAL_H

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

namespace global
{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	const int SPRITE_SCALE = 2;
}

namespace sides
{
	enum Side
	{
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		NONE
	};

	const inline Side getOppositeSide(Side side)
	{
		if (side == TOP)
			return BOTTOM;
		else if (side == BOTTOM)
			return TOP;
		else if (side == LEFT)
			return RIGHT;
		else if (side == RIGHT)
			return LEFT;
		else
			return NONE;
	}
}

enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct Vector2
{
	int x, y;
	Vector2() : x(0), y(0) {}
	Vector2(int _x, int _y) : x(_x), y(_y) {}
	static Vector2 zero() { return Vector2(0, 0); }
};

class Utils
{
public:
	//	Splits string *txt* wherever *ch* is found, then store all the substrings in vector *strs* and returns the size of the vector
	static unsigned int split(
		const std::string &txt,
		std::vector<std::string> &strs,
		char ch)
	{
		int pos = txt.find(ch);
		int initialPos = 0;
		strs.clear();
		while (pos != std::string::npos)
		{
			strs.push_back(txt.substr(initialPos, pos - initialPos));
			initialPos = pos + 1;
			pos = txt.find(ch, initialPos);
		}
		strs.push_back(txt.substr(initialPos, std::min<int>(pos,
															txt.size() - initialPos - 1)));
		return strs.size();
	}
};

#endif
