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

	std::map<std::string, SDL_Surface *> _spriteSheets;

public:
	Graphics();
	~Graphics();

	/*	SDL_Surface *loadImage
	 *	Loads an imgae into the _spriteSheets map if it doesn't already exist
	 */
	SDL_Surface *loadImage(const std::string &filePath);
};

#endif
