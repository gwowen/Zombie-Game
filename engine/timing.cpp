#include "timing.h"
#include <SDL2/SDL.h>

namespace Engine {

  fpsLimiter::fpsLimite() {

  }

  void fpsLimiter::init(float maxFPS) {
    setMaxFPS(maxFPS);
  }

  void fpsLimiter::setMaxFPS(float maxFPS) {
    _maxFPS = maxFPS;
  }

  void fpsLimiter::begin() {
    _startTicks = SDL_GetTicks();
  }

  float fpsLimiter::end() {
    calculateFPS();

    float frameTicks = SDL_GetTicks() - _startTicks();

    if(1000.0f / _maxFPS > frameTicks)
      SDL_Delay((Uint32)(1000.0f / _maxFPS -frameTicks));

    return _fps;
  }


  void fpsLimiter::calculateFPS() {
    
  }
}
