#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include "gltexture.h"

#include <string>

namespace Engine {

  //a 2D quad that we can render to the screen
  class Sprite {
  public:
    Sprite();
    ~Sprite();

    void init(float x, float y, float width, float height, std::string texturePath);

    void draw();

    float _x;
    float _y;
    float _width;
    float _height;
    GLuint _vboID;
    GLTexture _texture;
  };


}




#endif
