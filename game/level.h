#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "../engine/spritebatch.h"

class Level {
public:

  Level(const std::string& fileName);
  ~Level();

private:
  std::vector<std::string> _levelData;
  int _numHumans;

};


#endif
