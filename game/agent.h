#ifndef AGENT_H
#define AGENT_H

#include <glm/glm.hpp>
#include <string>
#include "../engine/spritebatch.h"

const float AGENT_WIDTH = 60.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Zombie;
class Human;


class Agent {

public:
  Agent();
  virtual ~Agent();

  virtual void update(const std::vector<std::string>& levelData,
                      std::vector<Human*>& humans,
                      std::vector<Zombie*>& zombies) = 0;

  void collideWithLevel(const std::vector<std::string>& levelData);

  void draw(Engine::SpriteBatch& _spriteBatch);

  //getters
  glm::vec2 getPosition() const { return _position;}

protected:
  glm::vec2 _position;
  Engine::Color _color;
  float _speed;


  void checkTilePosition(const std::vector<std::string>& levelData,
                          std::vector<glm::vec2> collideTilePositions,
                          float x, float y);

  void collideWithTile(glm::vec2 tilePos);

};



#endif
