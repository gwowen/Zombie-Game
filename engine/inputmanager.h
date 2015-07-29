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

    void update();

    void pressKey(unsigned int keyID);
    void releaseKey(unsigned int keyID);

    void setMouseCoords(float x, float y);

    //returns true if we hold the key down
    bool isKeyDown(unsigned int keyID);

    //returns true if the key was just pressed
    bool isKeyPressed(unsigned int keyID);

    glm::vec2 getMouseCoords() const { return _mouseCoords; }

  private:
    //returns true if the key is held down
    bool wasKeyDown(unsigned int keyID);
    std::unordered_map<unsigned int, bool> _keyMap;
    std::unordered_map<unsigned int, bool> _previousKeyMap;
    glm::vec2 _mouseCoords;


  };
}



#endif
