#include "timing.h"
#include <SDL2/SDL.h>

namespace Engine {

  fpsLimiter::fpsLimiter() {

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

    float frameTicks = (float)(SDL_GetTicks() - _startTicks);

    if(1000.0f / _maxFPS > frameTicks)
      SDL_Delay((Uint32)(1000.0f / _maxFPS - frameTicks));

    return _fps;
  }


  void fpsLimiter::calculateFPS() {
      //the number of frames to average
      static const int NUM_SAMPLES = 10;

      //stores all the frametimes for each frame that we will averages
      static float frameTimes[NUM_SAMPLES];

      //the current frame we are on
      static int currentFrame = 0;

      //the ticks of the previous frame
      static float prevTicks = SDL_GetTicks();

      //ticks for the current frame
      Uint32 currentTicks = SDL_GetTicks();

      //calculate the number of ticks (ms) for this frame
      _frameTime = (float)(currentTicks - prevTicks);
      frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

      //the number of frames to average
      int count;

      currentFrame++;
      if(currentFrame < NUM_SAMPLES) {
        count = currentFrame;
      } else {
        count = NUM_SAMPLES;
      }

      //average all the frame times
      float frameTimeAverage = 0;
      for(int i = 0; i < count ; ++i) {
        frameTimeAverage += frameTimes[i];
      }
      frameTimeAverage /= count;

      //calculate FPS
      if(frameTimeAverage > 0) {
        _fps = 1000.0f / frameTimeAverage;
      } else {
        _fps = 60.0f;
      }
  }

}
