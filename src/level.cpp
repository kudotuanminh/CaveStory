#include <level.h>

Level::Level() {}
Level::~Level() {}
Level::Level(
	std::string mapName,
	Vector2 spawnPoint,
	Graphics &graphics) : _mapName(mapName),
						  _spawnPoint(spawnPoint),
						  _size(Vector2(0, 0))
{
	this->loadMap(mapName, graphics);
}

void Level::loadMap(std::string mapName, Graphics &graphics)
{
	//	Parse XML file
	pugi::xml_document doc;
	std::stringstream ss;
	ss << "content/maps/" << mapName << ".tmx";
	doc.load_file(ss.str().c_str());

	pugi::xml_node mapNode = doc.child("map");

	//	Get the width and height of the whole map and store it in _size
	int width = atoi(mapNode.attribute("width").value()),
		height = atoi(mapNode.attribute("height").value());
	this->_size = Vector2(width, height);

	//	Get the width and height of the tiles and store it in _tileSize
	int tileWidth = atoi(mapNode.attribute("tilewidth").value()),
		tileHeight = atoi(mapNode.attribute("tileheight").value());
	this->_tileSize = Vector2(tileWidth, tileHeight);

	//	Loading the tilesets
	pugi::xml_node pTileset = mapNode.child("tileset");
	if (pTileset != NULL)
		while (pTileset)
		{
			const char *source = pTileset.child("image").attribute("source").value();
			char *path;
			std::stringstream ss;
			ss << source;
			int firstgid = atoi(pTileset.attribute("firstgid").value());
			SDL_Texture *tex = SDL_CreateTextureFromSurface(
				graphics.getRenderer(),
				graphics.loadImage(ss.str()));
			this->_tilesets.push_back(Tileset(tex, firstgid));

			pTileset = pTileset.next_sibling("tileset");
		}

	//	Loading the layers
	pugi::xml_node player = mapNode.child("layer");
	if (player != NULL)
		while (player)
		{
			//	Loading the data element
			pugi::xml_node pData = player.child("data");
			if (pData != NULL)
				while (pData)
				{
					//	Loading the tile element
					pugi::xml_node pTile = pData.child("tile");
					if (pTile != NULL)
					{
						int tileCounter = 0;
						while (pTile)
						{
							//	Build each individual tile here
							//	If gid = 0, no tile should be drawn, continue looping
							if (atoi(pTile.attribute("gid").value()) == 0)
							{
								tileCounter++;
								if (pTile.next_sibling("tile"))
								{
									pTile = pTile.next_sibling("tile");
									continue;
								}
								else
									break;
							}

							//	Get the tileset for this specific gid
							int gid = atoi(pTile.attribute("gid").value());
							Tileset tls;
							for (int i = 0; i < this->_tilesets.size(); i++)
								if (this->_tilesets[i].FirstGid <= gid)
								{
									//	This is the tileset we want
									tls = this->_tilesets.at(i);
									break;
								}
							if (tls.FirstGid == -1)
							{
								//	No tileset was found for this gid
								tileCounter++;
								if (pTile.next_sibling("tile"))
								{
									pTile = pTile.next_sibling("tile");
									continue;
								}
								else
									break;
							}

							//	Get the position of the tile in the level
							int xx = tileWidth * (tileCounter % width),
								yy = tileHeight * (tileCounter / width);
							Vector2 finalTilePosition = Vector2(xx, yy);

							//	Get the position of the tile in the tileset
							int tilesetWidth,
								tilesetHeight;
							SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
							int tsxx = tileWidth * (gid % (tilesetWidth / tileWidth) - 1),
								tsyy = tileHeight * (gid / (tilesetWidth / tileWidth) - 1);
							Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);

							//	Build the actual tile and add it to the level's tile list
							Tile tile(
								tls.Texture,
								Vector2(tileWidth, tileHeight),
								finalTilesetPosition,
								finalTilePosition);
							this->_tileList.push_back(tile);
							tileCounter++;

							pTile = pTile.next_sibling("tile");
						}
					}

					pData = pData.next_sibling("data");
				}

			player = player.next_sibling("layer");
		}
}

void Level::update(int elapsedTime)
{
}

//	Draws the background
void Level::draw(Graphics &graphics)
{
	for (int i = 0; i < this->_tileList.size(); i++)
		this->_tileList.at(i).draw(graphics);
}
