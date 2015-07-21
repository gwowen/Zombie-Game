#include "zombie.h"

#include "human.h"

Zombie::Zombie()
{

}

Zombie::~Zombie()
{

}

void Zombie::init(float speed, glm::vec2 pos) {
  _speed = speed;
  _position = pos;
  _health = 150;
  //set green color
  _color.r = 0;
  _color.g = 160;
  _color.b = 0;
  _color.a = 255;
}

void Zombie::update(const std::vector<std::string>& levelData,
                    std::vector<Human*>& humans,
                    std::vector<Zombie*>& zombies ) {

    //find the closest human
    Human* closestHuman = getNearestHuman(humans);

    //if we found a human, move towards him (or her!)
    if(closestHuman != nullptr) {
      glm::vec2 direction = glm::normalize(closestHuman->getPosition() - _position);
      _position += direction * _speed;
    }

    //do collision
    collideWithLevel(levelData);
}

Human* Zombie::getNearestHuman(std::vector<Human*>& humans) {

  Human* closestHuman = nullptr;
  float smallestDistance = 9999999.0f;

  for(int i = 0; i < humans.size(); ++i) {
    //get the direction vector
    glm::vec2 distVec = humans[i]->getPosition() - _position;
    //get distance
    float distance = glm::length(distVec);

    //if the person is closer than the closest person, this is the new closest
    if(distance < smallestDistance) {
      smallestDistance = distance;
      closestHuman = humans[i];
    }

  }

  return closestHuman;
}
