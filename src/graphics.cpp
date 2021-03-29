#include <graphics.h>

/*	Graphics class
 *	Dealing w/ graphics for the game
 */

Graphics::Graphics()
{
	// SDL_CreateWindowAndRenderer(
	// 	global::SCREEN_WIDTH,
	// 	global::SCREEN_HEIGHT,
	// 	0,
	// 	&this->_window,
	// 	&this->_renderer);
	// SDL_SetWindowTitle(this->_window, "ntm's Cave Story");

	this->_window = SDL_CreateWindow(
		"ntm's Cave Story",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		global::SCREEN_WIDTH,
		global::SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_PRESENTVSYNC);
}
Graphics::~Graphics()
{
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
}

//	Loads an imgae into the _spriteSheets map if not loaded before, then return the image from the map
SDL_Surface *Graphics::loadImage(const std::string &filePath)
{
	if (this->_spriteSheets.count(filePath) == 0)
		this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	return this->_spriteSheets[filePath];
}

//	Draws a texture to a certain part of the screen
void Graphics::blitSurface(
	SDL_Texture *texture,
	SDL_Rect *sourceRectangle,
	SDL_Rect *destinationRectangle)
{
	SDL_RenderCopy(
		this->_renderer,
		texture,
		sourceRectangle,
		destinationRectangle);
}

//	Renders everything to the screen
void Graphics::flip()
{
	SDL_RenderPresent(this->_renderer);
}

//	Clears the screen
void Graphics::clear()
{
	SDL_RenderClear(this->_renderer);
}

//	Returns the renderer
SDL_Renderer *Graphics::getRenderer() const
{
	return this->_renderer;
}
