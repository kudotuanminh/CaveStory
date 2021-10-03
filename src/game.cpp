#include <game.h>

namespace {
const int FPS = 50;
const int MAX_FRAME_TIME = 1000 / FPS;
}  // namespace

/*	Game class
 *	Holds all information for main game loop
 */

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    this->gameLoop();
}
Game::~Game() {}

void Game::gameLoop() {
    Graphics graphics;
    Input input;
    SDL_Event event;

    this->_level = Level("Map 1", graphics);
    this->_player = Player(graphics, this->_level.getPlayerSpawnPoint());
    this->_hud = HUD(graphics, this->_player);

    // this->_menu = Menu(graphics);
    // this->_menu.draw();

    int LAST_UPDATE_TIME = SDL_GetTicks();

    // Start the game loop
    while (true) {
        input.beginNewFrame();

        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
                input.keyDownEvent(event);
            if (event.type == SDL_KEYUP)
                input.keyUpEvent(event);
            if (event.type == SDL_QUIT)
                return;
        }
        if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
            return;
        if (input.isKeyHeld(SDL_SCANCODE_LEFT))
            this->_player.moveLeft();
        if (input.isKeyHeld(SDL_SCANCODE_RIGHT))
            this->_player.moveRight();

        if (input.isKeyHeld(SDL_SCANCODE_UP))
            this->_player.lookUp();
        if (input.isKeyHeld(SDL_SCANCODE_DOWN))
            this->_player.lookDown();
        if (input.wasKeyReleased(SDL_SCANCODE_UP))
            this->_player.stopLookingUp();
        if (input.wasKeyReleased(SDL_SCANCODE_DOWN))
            this->_player.stopLookingDown();

        if (input.isKeyHeld(SDL_SCANCODE_Z))
            this->_player.jump();
        if (!input.isKeyHeld(SDL_SCANCODE_LEFT) &&
            !input.isKeyHeld(SDL_SCANCODE_RIGHT))
            this->_player.stopMoving();

        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        if (MAX_FRAME_TIME > ELAPSED_TIME_MS)
            SDL_Delay(MAX_FRAME_TIME - ELAPSED_TIME_MS);
        this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME_MS;

        this->_graphics = graphics;
        this->draw(graphics);
    }
}

void Game::update(float elapsedTime) {
    this->_player.update(elapsedTime);
    this->_level.update(elapsedTime, this->_player);
    this->_hud.update(elapsedTime, this->_player);

    //	Check collisions
    std::vector<Rectangle> others =
        this->_level.checkTileCollisions(this->_player.getBoundingBox());
    if (others.size() > 0)
        this->_player.handleTileCollisions(others);

    //	Check slopes
    std::vector<Slope> otherSlopes =
        this->_level.checkSlopeCollisions(this->_player.getBoundingBox());
    if (otherSlopes.size() > 0)
        this->_player.handleSlopeCollisions(otherSlopes);

    //	Check doors
    std::vector<Door> otherDoors =
        this->_level.checkDoorCollisions(this->_player.getBoundingBox());
    if (otherDoors.size() > 0)
        this->_player.handleDoorCollisions(otherDoors, this->_level,
                                           this->_graphics);

    //	Check enemies
    std::vector<Enemy *> otherEnemies =
        this->_level.checkEnemyCollisions(this->_player.getBoundingBox());
    if (otherEnemies.size() > 0)
        this->_player.handleEnemyCollisions(otherEnemies);
}

void Game::draw(Graphics &graphics) {
    graphics.clear();
    this->_level.draw(graphics);
    this->_player.draw(graphics);
    this->_hud.draw(graphics);

    graphics.render();
}
