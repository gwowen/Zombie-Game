#ifndef AGENT_H
#define AGENT_H

#include <glm/glm.hpp>
#include "../engine/spritebatch.h"

const float AGENT_WIDTH = 60.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Zombie;
class Human;

class Agent {

public:
  Agent();
  virtual ~Agent();

  virtual void update() = 0;

  void draw(Engine::SpriteBatch& _spriteBatch);

  //getters
  glm::vec2 getPosition() const { return _position;}

protected:
  glm::vec2 _position;
  Engine::Color _color;
  float _speed;

};



#endif
