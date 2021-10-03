#ifndef HUD_H
#define HUD_H

#include <character.h>
#include <global.h>
#include <sprite.h>

class HUD {
   private:
    Player _player;

    //	HP
    Sprite _healthBarSprite, _healthNumber1, _currentHealthBar;

    // EXP
    Sprite _lvWord, _lvNumber, _expBar;

    //	Weapon
    Sprite _slash, _dashes;

   public:
    HUD();
    HUD(Graphics &graphics, Player &player);
    ~HUD();

    void update(int elapsedTime, Player &player);
    void draw(Graphics &graphics);
};

#endif
