#ifndef TILE_H
#define TILE_H

#include <global.h>
#include <graphics.h>

class Tile
{
protected:
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

class AnimatedTile : public Tile
{
private:
	std::vector<Vector2> _tilesetPositions;
	int _tileToDraw,
		_duration;

protected:
	int _amountOfTime = 0;
	bool _notDone = false;

public:
	AnimatedTile(
		std::vector<Vector2> tilesetPositions,
		int duration,
		SDL_Texture *tileset,
		Vector2 size,
		Vector2 position);

	void update(int elapsedTime);
	void draw(Graphics &graphics);
};

struct AnimatedTileInfo
{
public:
	int TilesetsFirstGid,
		StartTileID;
	std::vector<int> TileIDs;
	int Duration;
};

#endif
