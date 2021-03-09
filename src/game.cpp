#include <global.h>

#include <game.h>
#include <graphics.h>
#include <input.h>

/*	Game class
 *	Holds information for main game loop
 */

namespace
{
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
} // namespace

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game()
{
}

void Game::gameLoop()
{
	Graphics graphics;
	Input input;
	SDL_Event event;

	int LAST_UPDATE_TIME = SDL_GetTicks();

	// Starts game loop
	while (true)
	{
		input.beginNewFrame();

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN && !event.key.repeat)
				input.keyDownEvent(event);
			else if (event.type == SDL_KEYUP)
				input.keyUpEvent(event);
			else if (event.type == SDL_QUIT)
				return;
		}

		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
			return;
	}

	const int CURRENT_TIME_IN_MS = SDL_GetTicks();
	int ELAPSED_TIME_IN_MS = CURRENT_TIME_IN_MS - LAST_UPDATE_TIME;
	this->update(std::min(ELAPSED_TIME_IN_MS, MAX_FRAME_TIME));
	LAST_UPDATE_TIME = CURRENT_TIME_IN_MS;
}

void Game::draw(Graphics &graphics)
{
}

void Game::update(double elapsedTime)
{
}
