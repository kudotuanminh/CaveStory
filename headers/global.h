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

/*	Input class
 *	Keep tracks of keyboard states
 */

class Input
{
private:
	std::map<SDL_Scancode, bool> _heldKeys;
	std::map<SDL_Scancode, bool> _pressedKeys;
	std::map<SDL_Scancode, bool> _releasedKeys;

public:
	//	Reset keys that are no longer relevant
	void beginNewFrame()
	{
		this->_pressedKeys.clear();
		this->_releasedKeys.clear();
	}

	//	Key pressed
	void keyDownEvent(const SDL_Event &event)
	{
		this->_pressedKeys[event.key.keysym.scancode] = true;
		this->_heldKeys[event.key.keysym.scancode] = true;
	}

	//	Key released
	void keyUpEvent(const SDL_Event &event)
	{
		this->_releasedKeys[event.key.keysym.scancode] = true;
		this->_heldKeys[event.key.keysym.scancode] = false;
	}

	bool wasKeyPressed(SDL_Scancode key) { return this->_pressedKeys[key]; }
	bool wasKeyReleased(SDL_Scancode key) { return this->_releasedKeys[key]; }
	bool isKeyHeld(SDL_Scancode key) { return this->_heldKeys[key]; }
};

struct Vector2
{
	int x, y;
	Vector2() : x(0), y(0) {}
	Vector2(int _x, int _y) : x(_x), y(_y) {}
	static Vector2 zero() { return Vector2(0, 0); }
};

/*	Utils class
 *	Utilities
 */

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
