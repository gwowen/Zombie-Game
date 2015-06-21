#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
#include <glm/glm.hpp>

namespace Engine {
  class InputManager
  {
  public:
    InputManager();
    ~InputManager();

    void pressKey(unsigned int keyID);
    void releaseKey(unsigned key keyID);

    void setMouseCoords(float x, float y);
    bool isKeyPressed(unsigned int keyID);

    glm::vec2 getMouseCoords() const { return _mouseCoords; }

  private:
    std::unordered_map<unsigned int, bool> _keyMap;
    glm::vec2 _mouseCoords;

  };
}



#endif
