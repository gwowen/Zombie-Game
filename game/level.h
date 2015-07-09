#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "../engine/spritebatch.h"

const int TILE_WIDTH = 64;

class Level {
public:

  Level(const std::string& fileName);
  ~Level();

  void draw();

  //getters

  glm::vec2 getStartPlayerPos() const { return _startPlayerPos; }
  const std::vector<glm::vec2>& getZombieStartPositions() const { return _zombieStartPositions; }

private:
  std::vector<std::string> _levelData;
  int _numHumans;

  Engine::SpriteBatch _spriteBatch;

  glm::vec2 _startPlayerPos;
  std::vector<glm::vec2> _zombieStartPositions;

};


#endif
