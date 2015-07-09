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

  void draw(Engine::SpriteBatch& _spriteBatch);


protected:
  glm::vec2 _position;
  Engine::Color _color;
  float _speed;

};



#endif
