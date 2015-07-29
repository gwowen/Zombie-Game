#include "inputmanager.h"

namespace Engine {

  InputManager::InputManager() : _mouseCoords(0.0f)
  {

  }

  InputManager::~InputManager()
  {

  }

  void InputManager::update() {
    //loop through _keyMap using a for each loop, and copy it over to _previousKeyMap
    for(auto& it : _keyMap) {
      _previousKeyMap[it.first] = it.second;
    }
  }

  void InputManager::pressKey(unsigned int keyID) {
    //here we are treating _keyMap as an associative array.
    //if keyID doesn't alreadt exist in _keyMap, it will get added
    _keyMap[keyID] = true;
  }

  void InputManager::releaseKey(unsigned int keyID) {
    _keyMap[keyID] = false;
  }

  void InputManager::setMouseCoords(float x, float y) {
    _mouseCoords.x = x;
    _mouseCoords.y = y;
  }

  bool InputManager::isKeyDown(unsigned int keyID) {
    //we don't want to use the associative array approach here.
    //because we don't want to create a key if it doesn't exist, so we do it
    //manually
    auto it = _keyMap.find(keyID);
    if(it != _keyMap.end()) {
      //found the key
      return it->second;
    } else {
      //didn't find the key
      return false;
    }
  }

  bool InputManager::isKeyPressed(unsigned int keyID) {
    //check if it is pressed this frame, and wasn't pressed last frame
    if(isKeyDown(keyID) == true && wasKeyDown(keyID) == false)
      return true;

    return false;
  }

  bool InputManager::wasKeyDown(unsigned int keyID) {
    //we don't want to use an associative array approach here
    //because we don't want to create a key if it doesn't exist
    //so we do it manually
    auto it = _previousKeyMap.find(keyID);
    if(it != _previousKeyMap.end()) {
      //found the key
      return it->second;
    } else {
      //didn't find the key
      return false;
    }
  }


}
