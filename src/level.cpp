#include <level.h>

/*	Level class
 *	Reads and render maps' tiles, NPCs, player's spawn points from *.tmx
 *(XML based) map files
 */

Level::Level() {}
Level::Level(std::string mapName, Graphics &graphics)
    : _mapName(mapName), _size(Vector2(0, 0)) {
    this->loadMap(mapName, graphics);
}
Level::~Level() {}

void Level::loadMap(std::string mapName, Graphics &graphics) {
    //	Parse XML file
    pugi::xml_document doc;
    std::stringstream ss;
    ss << "content/maps/" << mapName << ".tmx";
    doc.load_file(ss.str().c_str());

    pugi::xml_node mapNode = doc.child("map");

    //	Get the width and height of the whole map and store it in _size
    int width = mapNode.attribute("width").as_int(),
        height = mapNode.attribute("height").as_int();
    this->_size = Vector2(width, height);

    //	Get the width and height of the tiles and store it in _tileSize
    int tileWidth = mapNode.attribute("tilewidth").as_int(),
        tileHeight = mapNode.attribute("tileheight").as_int();
    this->_tileSize = Vector2(tileWidth, tileHeight);

    //	Loading the tilesets
    for (pugi::xml_node pTileset = mapNode.child("tileset"); pTileset;
         pTileset = pTileset.next_sibling("tileset")) {
        const std::string source =
            pTileset.child("image").attribute("source").as_string();
        std::string path = "content/" + source.substr(3);
        std::stringstream ss;
        ss << path;
        int firstgid = pTileset.attribute("firstgid").as_int();
        SDL_Texture *tex = SDL_CreateTextureFromSurface(
            graphics.getRenderer(), graphics.loadImage(ss.str()));
        this->_tilesets.push_back(Tileset(tex, firstgid));

        //	Get animations for that tileset
        for (pugi::xml_node pTileA = pTileset.child("tile"); pTileA;
             pTileA = pTileA.next_sibling("tile")) {
            AnimatedTileInfo ati;
            ati.StartTileID = pTileA.attribute("id").as_int() + firstgid;
            ati.TilesetsFirstGid = firstgid;

            for (pugi::xml_node pAnimation = pTileA.child("animation");
                 pAnimation; pAnimation = pTileA.next_sibling("animation"))
                for (pugi::xml_node pFrame = pAnimation.child("frame"); pFrame;
                     pFrame = pFrame.next_sibling("frame")) {
                    ati.TileIDs.push_back(pFrame.attribute("tileid").as_int() +
                                          firstgid);
                    ati.Duration = pFrame.attribute("duration").as_int();
                }

            this->_animatedTileInfos.push_back(ati);
        }
    }

    //	Loading the layers
    for (pugi::xml_node pLayer = mapNode.child("layer"); pLayer;
         pLayer = pLayer.next_sibling("layer")) {
        //	Loading the data element
        for (pugi::xml_node pData = pLayer.child("data"); pData;
             pData = pData.next_sibling("data")) {
            //	Loading the tile element
            pugi::xml_node pTile = pData.child("tile");
            if (pTile) {
                int tileCounter = 0;
                while (pTile) {
                    //	Build each individual tile here
                    //	If gid = 0, no tile should be drawn, continue looping
                    if (pTile.attribute("gid").as_int() == 0) {
                        tileCounter++;
                        if (pTile.next_sibling("tile")) {
                            pTile = pTile.next_sibling("tile");
                            continue;
                        } else
                            break;
                    }

                    //	Get the tileset for this specific gid
                    int gid = pTile.attribute("gid").as_int();
                    Tileset tls;
                    int closest = 0;
                    for (int i = 0; i < this->_tilesets.size(); i++)
                        if (this->_tilesets[i].FirstGid <= gid)
                            if (this->_tilesets[i].FirstGid > closest) {
                                closest = this->_tilesets[i].FirstGid;
                                tls = this->_tilesets[i];
                            }
                    if (tls.FirstGid == -1) {
                        //	No tileset was found for this gid
                        tileCounter++;
                        if (pTile.next_sibling("tile")) {
                            pTile = pTile.next_sibling("tile");
                            continue;
                        } else
                            break;
                    }

                    //	Get the position of the tile in the level
                    int xx = 0, yy = 0;
                    xx = tileWidth * (tileCounter % width);
                    yy = tileHeight * (tileCounter / width);
                    Vector2 finalTilePosition = Vector2(xx, yy);

                    //	Build the actual tile and add it to the level's tile
                    // list
                    bool isAnimatedTile = false;
                    AnimatedTileInfo currATI;
                    for (int i = 0; i < this->_animatedTileInfos.size(); i++)
                        if (this->_animatedTileInfos[i].StartTileID == gid) {
                            currATI = this->_animatedTileInfos[i];
                            isAnimatedTile = true;
                            break;
                        }

                    if (isAnimatedTile) {
                        std::vector<Vector2> tilesetPositions;
                        for (int i = 0; i < currATI.TileIDs.size(); i++)
                            tilesetPositions.push_back(this->getTilesetPosition(
                                tls, currATI.TileIDs[i], tileWidth,
                                tileHeight));
                        AnimatedTile tile(
                            tilesetPositions, currATI.Duration, tls.Texture,
                            Vector2(tileWidth, tileHeight), finalTilePosition);
                        this->_animatedTileList.push_back(tile);
                    } else {
                        Vector2 finalTilesetPosition = this->getTilesetPosition(
                            tls, gid, tileWidth, tileHeight);
                        Tile tile(tls.Texture, Vector2(tileWidth, tileHeight),
                                  finalTilesetPosition, finalTilePosition);
                        this->_tileList.push_back(tile);
                    }

                    tileCounter++;
                    pTile = pTile.next_sibling("tile");
                }
            }
        }
    }

    //	Loading object groups
    for (pugi::xml_node pObjectGroup = mapNode.child("objectgroup");
         pObjectGroup;
         pObjectGroup = pObjectGroup.next_sibling("objectgroup")) {
        const std::string name = pObjectGroup.attribute("name").as_string();
        std::stringstream ss;
        ss << name;

        //	Loading 'collisions' data
        if (ss.str() == "collisions")
            for (pugi::xml_node pObject = pObjectGroup.child("object"); pObject;
                 pObject = pObject.next_sibling("object")) {
                float x = pObject.attribute("x").as_float(),
                      y = pObject.attribute("y").as_float(),
                      width = pObject.attribute("width").as_float(),
                      height = pObject.attribute("height").as_float();
                this->_collisionRects.push_back(
                    Rectangle(global::SPRITE_SCALE * std::ceil(x),
                              global::SPRITE_SCALE * std::ceil(y),
                              global::SPRITE_SCALE * std::ceil(width),
                              global::SPRITE_SCALE * std::ceil(height)));
            }

        // Loading 'slopes' data
        else if (ss.str() == "slopes")
            for (pugi::xml_node pObject = pObjectGroup.child("object"); pObject;
                 pObject = pObject.next_sibling("object")) {
                std::vector<Vector2> points;
                int x = std::ceil(pObject.attribute("x").as_float()),
                    y = std::ceil(pObject.attribute("y").as_float());
                Vector2 p1 = Vector2(x, y);

                std::vector<std::string> pairs;
                const std::string pointString =
                    pObject.child("polyline").attribute("points").as_string();
                //	Splitting to pairs of slope point
                std::stringstream ss;
                ss << pointString;

                Utils::split(ss.str(), pairs, ' ');
                //	Gotten pairs of point, now loop through, split to
                // Vector2s then store them to points vector
                for (int i = 0; i < pairs.size(); i++) {
                    std::vector<std::string> ps;
                    Utils::split(pairs[i], ps, ',');
                    int pointX = std::ceil(std::stoi(ps[0])),
                        pointY = std::ceil(std::stoi(ps[1]));
                    points.push_back(Vector2(pointX, pointY));
                }

                for (int i = 0; i < points.size() - 1; i++) {
                    int x1 = global::SPRITE_SCALE * (p1.x + points[i].x),
                        y1 = global::SPRITE_SCALE * (p1.y + points[i].y),
                        x2 = global::SPRITE_SCALE * (p1.x + points[i + 1].x),
                        y2 = global::SPRITE_SCALE * (p1.y + points[i + 1].y);
                    this->_slopes.push_back(
                        Slope(Vector2(x1, y1), Vector2(x2, y2)));
                }
            }

        //	Loading 'spawn points' data
        else if (ss.str() == "spawn points")
            for (pugi::xml_node pObject = pObjectGroup.child("object"); pObject;
                 pObject = pObject.next_sibling("object")) {
                float x = pObject.attribute("x").as_float(),
                      y = pObject.attribute("y").as_float();
                std::string name = pObject.attribute("name").as_string();
                std::stringstream ss;
                ss << name;
                if (ss.str() == "player") {
                    this->_spawnPoint =
                        Vector2(global::SPRITE_SCALE * std::ceil(x),
                                global::SPRITE_SCALE * std::ceil(y));
                }
            }

        //	Loading 'doors' data
        else if (ss.str() == "doors")
            for (pugi::xml_node pObject = pObjectGroup.child("object"); pObject;
                 pObject = pObject.next_sibling("object")) {
                float x = pObject.attribute("x").as_float(),
                      y = pObject.attribute("y").as_float(),
                      w = pObject.attribute("width").as_float(),
                      h = pObject.attribute("height").as_float();
                Rectangle rect = Rectangle(x, y, w, h);

                for (pugi::xml_node pProperties = pObject.child("properties");
                     pProperties;
                     pProperties = pProperties.next_sibling("properties"))
                    for (pugi::xml_node pProperty =
                             pProperties.child("property");
                         pProperty;
                         pProperty = pProperty.next_sibling("property")) {
                        std::string name =
                            pProperty.attribute("name").as_string();
                        std::stringstream ss;
                        ss << name;
                        if (ss.str() == "destination") {
                            std::string value =
                                pProperty.attribute("value").as_string();
                            std::stringstream ss2;
                            ss2 << value;
                            Door door = Door(rect, ss2.str());
                            this->_doorList.push_back(door);
                        }
                    }
            }

        //	Loading 'enemies' data
        else if (ss.str() == "enemies") {
            for (pugi::xml_node pObject = pObjectGroup.child("object"); pObject;
                 pObject = pObject.next_sibling("object")) {
                float x = pObject.attribute("x").as_float(),
                      y = pObject.attribute("y").as_float();

                std::string name = pObject.attribute("name").as_string();
                std::stringstream ss;
                ss << name;
                if (ss.str() == "bat") {
                    this->_enemies.push_back(
                        new Bat(graphics,
                                Vector2(global::SPRITE_SCALE * std::floor(x),
                                        global::SPRITE_SCALE * std::floor(y))));
                }
            }
        }

        //	other objectgroup can be added here
    }
}

Vector2 Level::getTilesetPosition(Tileset tls, int gid, int tileWidth,
                                  int tileHeight) {
    int tilesetWidth, tilesetHeight, tsxx = 0, tsyy = 0;
    SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
    tsxx = tileWidth * ((gid - 1) % (tilesetWidth / tileWidth));
    tsyy = tileHeight * ((gid - tls.FirstGid) / (tilesetWidth / tileWidth));
    return Vector2(tsxx, tsyy);
}

const Vector2 Level::getPlayerSpawnPoint() const { return this->_spawnPoint; }

std::vector<Rectangle> Level::checkTileCollisions(const Rectangle &other) {
    std::vector<Rectangle> others;
    for (int i = 0; i < this->_collisionRects.size(); i++)
        if (this->_collisionRects[i].collidesWith(other))
            others.push_back(this->_collisionRects[i]);
    return others;
}

std::vector<Slope> Level::checkSlopeCollisions(const Rectangle &other) {
    std::vector<Slope> others;
    for (int i = 0; i < this->_slopes.size(); i++)
        if (this->_slopes[i].collidesWith(other))
            others.push_back(this->_slopes[i]);
    return others;
}

std::vector<Door> Level::checkDoorCollisions(const Rectangle &other) {
    std::vector<Door> others;
    for (int i = 0; i < this->_doorList.size(); i++)
        if (this->_doorList[i].collidesWith(other))
            others.push_back(this->_doorList[i]);
    return others;
}

std::vector<Enemy *> Level::checkEnemyCollisions(const Rectangle &other) {
    std::vector<Enemy *> others;
    for (int i = 0; i < this->_enemies.size(); i++)
        if (this->_enemies[i]->getBoundingBox().collidesWith(other))
            others.push_back(this->_enemies[i]);
    return others;
}

void Level::update(int elapsedTime, Player &player) {
    for (int i = 0; i < this->_animatedTileList.size(); i++)
        this->_animatedTileList[i].update(elapsedTime);
    for (int i = 0; i < this->_enemies.size(); i++)
        this->_enemies[i]->update(elapsedTime, player);
}

void Level::draw(Graphics &graphics) {
    for (int i = 0; i < this->_tileList.size(); i++)
        this->_tileList[i].draw(graphics);
    for (int i = 0; i < this->_animatedTileList.size(); i++)
        this->_animatedTileList[i].draw(graphics);
    for (int i = 0; i < this->_enemies.size(); i++)
        this->_enemies[i]->draw(graphics);
}
