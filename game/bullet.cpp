#include "bullet.h"
#include "../engine/resourcemanager.h"

#include "agent.h"
#include "human.h"
#include "zombie.h"
#include "level.h"



Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed) :
  _position(position),
  _direction(direction),
  _damage(damage),
  _speed(speed) {

  }

  Bullet::~Bullet() {

  }

  bool Bullet::update(const std::vector<std::string>& levelData) {
    _position += _direction * _speed;
    return collideWithWorld(levelData);
  }

  void Bullet::draw(Engine::SpriteBatch& spriteBatch) {
    glm::vec4 destRect(_position.x + BULLET_RADIUS,
                       _position.y + BULLET_RADIUS,
                      BULLET_RADIUS * 2,
                      BULLET_RADIUS * 2);

   const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

   Engine::Color color;

   color.r = 75;
   color.g = 75;
   color.b = 75;
   color.a = 255;

   spriteBatch.draw(destRect, uvRect, Engine::ResourceManager::getTexture("../../game/Textures/circle.png").id, 0.0f, color);
  }

  bool Bullet::collideWithAgent(Agent* agent) {
    const float MIN_DISTANCE = AGENT_RADIUS + BULLET_RADIUS;

    glm::vec2 centerPosA = _position;
    glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

    glm::vec2 distVec = centerPosA - centerPosB;

    float distance = glm::length(distVec);

    float collisionDepth = MIN_DISTANCE - distance;
    if(collisionDepth > 0) {
      return true;
    }

    return false;
  }

  bool Bullet::collideWithWorld(const std::vector<std::string>& levelData) {
    glm::ivec2 gridPosition;
    gridPosition.x = floor(_position.x / (float)TILE_WIDTH);
    gridPosition.y = floor(_position.y / (float)TILE_WIDTH);

  //if we're going to be going outside the world, return collision
    if(gridPosition.x < 0 || gridPosition.x >= levelData[0].size() ||
      gridPosition.y < 0 || gridPosition.y >= levelData.size())
        return true;

      return(levelData[gridPosition.y][gridPosition.x] != '.');
}
