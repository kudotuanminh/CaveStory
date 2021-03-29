#include <tile.h>

Tile::Tile() {}
Tile::Tile(
	SDL_Texture *tileset,
	Vector2 size,
	Vector2 tilesetPosition,
	Vector2 position) : _tileset(tileset),
						_size(size),
						_tilesetPosition(tilesetPosition),
						_position(Vector2(position.x * global::SPRITE_SCALE,
										  position.y * global::SPRITE_SCALE)) {}

void Tile::update(int elapsedTime)
{
}

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
		static_cast<int>(this->_size.x * global::SPRITE_SCALE),
		static_cast<int>(this->_size.y * global::SPRITE_SCALE)};

	graphics.blitSurface(
		this->_tileset,
		&sourceRect,
		&destRect);
}
