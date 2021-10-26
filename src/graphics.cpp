#include <graphics.h>

/*	Graphics class
 *	Dealing w/ graphics for the game
 */

Graphics::Graphics() {
    this->_window = SDL_CreateWindow(
        "ntm's Cave Story", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        global::SCREEN_WIDTH, global::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    this->_renderer =
        SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_PRESENTVSYNC);
}
Graphics::~Graphics() {
    SDL_DestroyWindow(this->_window);
    SDL_DestroyRenderer(this->_renderer);
}

SDL_Renderer *Graphics::getRenderer() const { return this->_renderer; }

SDL_Surface *Graphics::loadImage(const std::string &filePath) {
    if (this->_spriteSheets.count(filePath) == 0)
        this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
    return this->_spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture *texture, SDL_Rect *sourceRectangle,
                           SDL_Rect *destinationRectangle) {
    SDL_RenderCopy(this->_renderer, texture, sourceRectangle,
                   destinationRectangle);
}

void Graphics::render() { SDL_RenderPresent(this->_renderer); }
void Graphics::clear() { SDL_RenderClear(this->_renderer); }
