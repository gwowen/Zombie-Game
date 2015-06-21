#ifndef TIMING_H
#define TIMING_H

namespace Engine {
  class fpsLimiter {
  public:
    fpsLimiter();

    void init(float maxFPS);
    void setMaxFPS(float maxFPS);

    void begin();
    void end();

    float end();

  private:
    void calculateFPS();

    float _fps;
    float _maxFPS;
    float _frameTime;
    unsigned int _startTicks;
  };
}


#endif
