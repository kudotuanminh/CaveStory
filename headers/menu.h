#ifndef MENU_H
#define MENU_H

#include <global.h>
#include <graphics.h>

class Menu {
   private:
    Graphics _graphics;
    SDL_Texture *_menu, *_menuAnimations;

   public:
    Menu();
    Menu(Graphics &graphics);
    ~Menu();

    void draw();
};

#endif
