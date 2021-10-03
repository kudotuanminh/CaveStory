#ifndef LEVEL_H
#define LEVEL_H

#include <character.h>
#include <global.h>
#include <shapes.h>
#include <tile.h>

#include <pugixml.hpp>

class Enemy;
class Player;

struct Tileset {
    SDL_Texture *Texture;
    int FirstGid;

    Tileset() { this->FirstGid = -1; }
    Tileset(SDL_Texture *Texture, int FirstGid) {
        this->Texture = Texture;
        this->FirstGid = FirstGid;
    }
};

class Level {
   private:
    std::string _mapName;
    Vector2 _spawnPoint;

    Vector2 _size;
    Vector2 _tileSize;

    SDL_Texture *_backgroundTexture;

    std::vector<Tile> _tileList;
    std::vector<Tileset> _tilesets;
    std::vector<Rectangle> _collisionRects;
    std::vector<Slope> _slopes;

    std::vector<AnimatedTile> _animatedTileList;
    std::vector<AnimatedTileInfo> _animatedTileInfos;

    std::vector<Door> _doorList;

    std::vector<Enemy *> _enemies;

    void loadMap(std::string mapName, Graphics &graphics);

    Vector2 getTilesetPosition(Tileset tls, int gid, int tileWidth,
                               int tileHeight);

   public:
    Level();
    Level(std::string mapName, Graphics &graphics);
    ~Level();

    const Vector2 getPlayerSpawnPoint() const;

    std::vector<Rectangle> checkTileCollisions(const Rectangle &other);
    std::vector<Slope> checkSlopeCollisions(const Rectangle &other);
    std::vector<Door> checkDoorCollisions(const Rectangle &other);
    std::vector<Enemy *> checkEnemyCollisions(const Rectangle &other);

    void update(int elapsedTime, Player &player);
    void draw(Graphics &graphics);
};

#endif
