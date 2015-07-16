#ifndef GUN_H
#define GUN_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include  "bullet.h"


class Gun {
public:
  Gun(std::string name, int fireRate, int bulletsPerShot, float spread, float bulletDamage, float bulletSpeed);
  ~Gun();

  void update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets);

private:

  void fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Bullet>& bullets);

  std::string _name;

  int _fireRate; // fire rate in terms of frames

  int _bulletsPerShot; //how many bullets are fired at the time

  float _spread; //accuracy

  float _bulletSpeed;

  int _bulletDamage;

  int _frameCounter; //counts frames so we know when to shoot bullets

};


#endif
