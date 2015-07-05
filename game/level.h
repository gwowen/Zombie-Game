#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "../engine/spritebatch.h"

class Level {
public:

  Level(const std::string& fileName);
  ~Level();

  void draw();

private:
  std::vector<std::string> _levelData;
  int _numHumans;

  Engine::SpriteBatch _spriteBatch;

  glm::ivec2 _startPlayerPos;
  std::vector<glm::ivec2> _zombieStartPositions;

};


#endif
