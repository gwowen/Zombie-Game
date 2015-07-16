#ifndef BULLET_H
#define BULLET_H

#include <glm/glm.hpp>
#include <vector>
#include "../engine/spritebatch.h"
#include <string>



class Human;
class Zombie;
class Agent;

const int BULLET_RADIUS = 5;

class Bullet {
public:
  Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed);
  ~Bullet();

  //when update returns true, we delete the bullet
  bool update(const std::vector<std::string>& levelData);

  void draw(Engine::SpriteBatch& spriteBatch);

  bool collideWithAgent(Agent* agent);

  float getDamage() const {   return _damage; }

private:
  bool collideWithWorld(const std::vector<std::string>& levelData);

  glm::vec2 _position;
  glm::vec2 _direction;
  float _damage;
  float _speed;

};


#endif
