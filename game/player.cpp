#include "player.h"
#include <SDL2/SDL.h>

Player::Player() :
    _currentGunIndex(-1)
{

}

Player::~Player()
{

}

void Player::init(float speed, glm::vec2 pos, Engine::InputManager* inputManager, Engine::Camera2D* camera, std::vector<Bullet>* bullets)
{
  _speed = speed;
  _position = pos;
  _inputManager = inputManager;
  _bullets = bullets;
  _camera = camera;
  _color.r = 0;
  _color.g = 0;
  _color.b = 185;
  _color.a = 255;
  _health = 150;

}

void Player::addGun(Gun* gun) {
  //add the gun to the inventory
  _guns.push_back(gun);

  //if no gun is equipped, equip one!
  if(_currentGunIndex == -1)
    _currentGunIndex = 0;
}

void Player::update(const std::vector<std::string>& levelData,
                    std::vector<Human*>& humans,
                    std::vector<Zombie*>& zombies) {
  if(_inputManager->isKeyPressed(SDLK_w)) {
    _position.y += _speed;
  } else if (_inputManager->isKeyPressed(SDLK_s)) {
    _position.y -= _speed;
  }

  if(_inputManager->isKeyPressed(SDLK_a)) {
    _position.x -= _speed;
  } else if (_inputManager->isKeyPressed(SDLK_d)) {
    _position.x += _speed;
  }

  collideWithLevel(levelData);

}
