#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "agent.h"

class Zombie : public Agent {
public:
  Zombie();
  ~Zombie();

  virtual void update();

};




#endif
