#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <global.h>

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
   private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;

    std::map<std::string, SDL_Surface *> _spriteSheets;

   public:
    Graphics();
    ~Graphics();

    SDL_Renderer *getRenderer() const;

    SDL_Surface *loadImage(const std::string &filePath);
    void blitSurface(SDL_Texture *texture, SDL_Rect *sourceRectangle,
                     SDL_Rect *destinationRectangle);

    void render();
    void clear();
};

#endif
