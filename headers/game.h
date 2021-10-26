#ifndef GAME_H
#define GAME_H

#include <HUD.h>
#include <global.h>
#include <level.h>

class Game {
   private:
    Player _player;
    Level _level;
    HUD _hud;
    Graphics _graphics;

    void gameLoop();

    void update(float elapsedTime);
    void draw(Graphics &graphics);

   public:
    Game();
    ~Game();
};

#endif
