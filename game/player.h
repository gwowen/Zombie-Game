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


  void init(float speed, glm::vec2 position, Engine::InputManager* inputManager);

  void update();



private:
  Engine::InputManager* _inputManager;

};




#endif
