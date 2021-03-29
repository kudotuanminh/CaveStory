#ifndef LEVEL_H
#define LEVEL_H

#include <global.h>
#include <graphics.h>
#include <tile.h>

#include <pugixml.hpp>

struct Tileset
{
	SDL_Texture *Texture;
	int FirstGid;

	Tileset()
	{
		this->FirstGid = -1;
	}
	Tileset(SDL_Texture *Texture, int FirstGid)
	{
		this->Texture = Texture;
		this->FirstGid = FirstGid;
	}
};

class Level
{
private:
	std::string _mapName;
	Vector2 _spawnPoint;

	Vector2 _size;
	Vector2 _tileSize;

	SDL_Texture *_backgroundTexture;

	std::vector<Tile> _tileList;
	std::vector<Tileset> _tilesets;

	void loadMap(std::string mapName, Graphics &graphics);

public:
	Level();
	Level(
		std::string mapName,
		Vector2 spawnPoint,
		Graphics &graphics);
	~Level();

	void update(int elapsedTime);
	void draw(Graphics &graphics);
};

#endif
