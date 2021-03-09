#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <global.h>

struct SDL_Window;
struct SDL_Renderer;

/*	Graphics class
 *	Dealing graphics for the game
 */

class Graphics
{
private:
	SDL_Window *_window;
	SDL_Renderer *_renderer;

	//	Stores sprite sheets
	std::map<std::string, SDL_Surface *> _spriteSheets;

public:
	Graphics();
	~Graphics();

	SDL_Surface *loadImage(const std::string &filePath);
	void blitSurface(SDL_Texture *texture, SDL_Rect *sourceRectangle, SDL_Rect *destinationRectangle);
	void flip();
	void clear();
	SDL_Renderer *getRenderer() const;
};

#endif
