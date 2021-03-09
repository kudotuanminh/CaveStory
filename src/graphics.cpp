#include <graphics.h>

/*	Graphics class
 *	Dealing graphics for the game
 */

Graphics::Graphics()
{
	SDL_CreateWindowAndRenderer(640, 480, 0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "ntm's Cave Story");
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(this->_window);
}
