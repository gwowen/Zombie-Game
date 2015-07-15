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

};


#endif
