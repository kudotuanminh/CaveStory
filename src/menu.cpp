#include <menu.h>

Menu::Menu() {}
Menu::Menu(Graphics &graphics) {
    this->_graphics = graphics;
    this->_menu = SDL_CreateTextureFromSurface(
        this->_graphics.getRenderer(),
        this->_graphics.loadImage("content/backgrounds/bkMenu.png"));
    this->_menuAnimations = SDL_CreateTextureFromSurface(
        this->_graphics.getRenderer(),
        this->_graphics.loadImage("content/backgrounds/bkMenuAnimated.png"));
}
Menu::~Menu() {}

void Menu::draw() {
    SDL_RenderCopy(this->_graphics.getRenderer(), this->_menu, NULL, NULL);

    for (int i = 0; i < 50; i++) {
        SDL_Delay(200);

        SDL_Rect sourceRect = {(i % 5) * 52, 0, 52, 70};

        SDL_Rect destRect = {191, 197, 52, 70};

        SDL_RenderCopy(this->_graphics.getRenderer(), this->_menu, &sourceRect,
                       &destRect);
    }
}

/*
w start 191
h start 197
w 52
h 70
*/
