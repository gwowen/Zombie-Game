#include "texturecache.h"
#include "imageloader.h"

namespace Engine {

  TextureCache::TextureCache()
  {

  }

  TextureCache::~TextureCache()
  {

  }

  GLTexture TextureCache::getTexture(std::string texturePath) {

    //iterate through the map to see if the texture is in it
    auto mit = _textureMap.find(texturePath);

    //check if it's not in the map
    if(mit == _textureMap.end()) {

      //load the texture
      GLTexture newTexture = ImageLoader::loadPNG(texturePath);

      //insert into the map
      _textureMap.insert(make_pair(texturePath, newTexture));

      return newTexture;
    }

    //return the value from the map
    return mit->second;
  }


}
