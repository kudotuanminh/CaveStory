#ifndef CHARACTER_H
#define CHARACTER_H

#include <global.h>
#include <level.h>
#include <sprite.h>

class Level;
class Enemy;

namespace player_constants {
const float WALK_SPEED = 0.2f;
const float JUMP_SPEED = 0.7f;

const float GRAVITY = 0.002f;
const float GRAVITY_CAP = 0.8f;
}  // namespace player_constants

class Player : public AnimatedSprite {
   private:
    float _dx, _dy;
    Direction _facing;
    bool _grounded, _lookingUp, _lookingDown;
    int _maxHealth, _currentHealth;

   public:
    Player();
    Player(Graphics &graphics, Vector2 spawnPoint);
    ~Player();

    const float getX() const;
    const float getY() const;

    const int getMaxHealth() const;
    const int getCurrentHealth() const;

    virtual void setupAnimations();
    virtual void animationDone(std::string currentAnimation);

    void moveLeft();
    void moveRight();
    void stopMoving();

    void lookUp();
    void stopLookingUp();
    void lookDown();
    void stopLookingDown();

    void jump();

    void handleTileCollisions(std::vector<Rectangle> &others);
    void handleSlopeCollisions(std::vector<Slope> &others);
    void handleDoorCollisions(std::vector<Door> &others, Level &level,
                              Graphics &graphics);
    void handleEnemyCollisions(std::vector<Enemy *> &others);

    void gainHealth(int amt);

    void update(float elapsedTime);
    void draw(Graphics &graphics);
};

class Enemy : public AnimatedSprite {
   protected:
    Direction _direction;

    int _maxHealth, _currentHealth;

   public:
    Enemy();
    Enemy(Graphics &graphics, std::string filePath, int sourceX, int sourceY,
          int width, int height, Vector2 spawnPoint, int timeToUpdate);
    ~Enemy();

    const int getMaxHealth();
    const int getCurrentHealth();

    virtual void touchPlayer(Player *player) = 0;

    virtual void update(int elapsedTime, Player &player);
    virtual void draw(Graphics &graphics);
};

class Bat : public Enemy {
   private:
    float _startingX, _startingY;
    bool _shouldMoveUp;

   public:
    Bat();
    Bat(Graphics &graphics, Vector2 spawnPoint);
    ~Bat();

    void animationDone(std::string currentAnimation);
    void setupAnimations();

    void touchPlayer(Player *player);

    void update(int elapsedTime, Player &player);
    void draw(Graphics &graphics);
};

#endif
