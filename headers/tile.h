#ifndef TILE_H
#define TILE_H

#include <global.h>
#include <graphics.h>

class Tile
{
private:
	SDL_Texture *_tileset;
	Vector2 _size, _tilesetPosition, _position;

public:
	Tile();
	Tile(
		SDL_Texture *tileset,
		Vector2 size,
		Vector2 tilesetPosition,
		Vector2 position);

	void update(int elapsedTime);
	void draw(Graphics &graphics);
};

#endif
