#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "texturecache.h"
#include <string>

namespace Engine {

  //this class holds all resources, such as models and textures
  class ResourceManager {
  public:
    static GLTexture getTexture(std::string texturePath);

  private:
    static TextureCache _textureCache;
  };


}


#endif
