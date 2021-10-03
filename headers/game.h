#ifndef GAME_H
#define GAME_H

#include <HUD.h>
#include <global.h>
#include <level.h>
#include <menu.h>

class Game {
   private:
    Graphics _graphics;
    Player _player;
    Level _level;
    HUD _hud;
    Menu _menu;

    void gameLoop();

    void update(float elapsedTime);
    void draw(Graphics &graphics);

   public:
    Game();
    ~Game();
};

#endif
