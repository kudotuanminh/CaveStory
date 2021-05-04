#include <tile.h>

/*	Tile class
 *	Handles rendering tiles from tilesets to renderer
 */

Tile::Tile() {}
Tile::Tile(
	SDL_Texture *tileset,
	Vector2 size,
	Vector2 tilesetPosition,
	Vector2 position) : _tileset(tileset),
						_size(size),
						_tilesetPosition(tilesetPosition),
						_position(Vector2(global::SPRITE_SCALE * position.x,
										  global::SPRITE_SCALE * position.y)) {}
Tile::~Tile() {}

void Tile::update(int elapsedTime) {}

void Tile::draw(Graphics &graphics)
{
	SDL_Rect sourceRect = {
		this->_tilesetPosition.x,
		this->_tilesetPosition.y,
		this->_size.x,
		this->_size.y};

	SDL_Rect destRect = {
		this->_position.x,
		this->_position.y,
		global::SPRITE_SCALE * this->_size.x,
		global::SPRITE_SCALE * this->_size.y};

	graphics.blitSurface(
		this->_tileset,
		&sourceRect,
		&destRect);
}

/*	AnimatedTile class
 *	Holds logic for animating tiles
 */

AnimatedTile::AnimatedTile(
	std::vector<Vector2> tilesetPositions,
	int duration,
	SDL_Texture *tileset,
	Vector2 size,
	Vector2 position) : Tile(tileset,
							 size,
							 tilesetPositions[0],
							 position),
						_tilesetPositions(tilesetPositions),
						_duration(duration),
						_tileToDraw(0) {}
AnimatedTile::~AnimatedTile() {}

void AnimatedTile::update(int elapsedTime)
{
	if (this->_amountOfTime <= 0)
	{
		if (this->_tileToDraw == this->_tilesetPositions.size() - 1)
			this->_tileToDraw = 0;
		else
			this->_tileToDraw++;
		this->_amountOfTime = this->_duration;
	}
	else
		this->_amountOfTime -= elapsedTime;

	Tile::update(elapsedTime);
}

void AnimatedTile::draw(Graphics &graphics)
{
	SDL_Rect sourceRect = {
		this->_tilesetPositions[this->_tileToDraw].x,
		this->_tilesetPositions[this->_tileToDraw].y,
		this->_size.x,
		this->_size.y};

	SDL_Rect destRect = {
		this->_position.x,
		this->_position.y,
		global::SPRITE_SCALE * this->_size.x,
		global::SPRITE_SCALE * this->_size.y};

	graphics.blitSurface(
		this->_tileset,
		&sourceRect,
		&destRect);
}
