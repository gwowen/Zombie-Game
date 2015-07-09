#ifndef PLAYER_H
#define PLAYER_H

#include "human.h"
#include "../engine/inputmanager.h"
#include "../engine/camera2d.h"
#include "bullet.h"

class Gun;

class Player : public Human {
public:
  Player();
  virtual ~Player();


  void init(int speed, glm::vec2 position);

  void update(Engine::InputManager& inputManager);

};




#endif
