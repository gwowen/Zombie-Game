#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <map>
#include "gltexture.h"

namespace Engine {

  //this caches the textures so multiple sprites can use the same textures
  class TextureCache
  {
  public:
    TextureCache();
    ~TextureCache();

    GLTexture getTexture(std::string texturePath);

  private:
    std::map<std::string, GLTexture> _textureMap;
  };

}

#endif
