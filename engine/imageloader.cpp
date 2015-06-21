#include "imageloader.h"
#include "picoPNG.h"
#include "iomanager.h"
#include "errors.h"

namespace Engine {
  GLTexture ImageLoader::loadPNG(std::string filePath) {
    //create a GLTexture, initialize all fields to zero
    GLTexture texture = {};

    //this is the input data to decodePNG, which we load from a file
    std::vector<unsigned char> in;
    //this is the output data from decodePNG, which is the pixel data for our texture
    std::vector<unsigned char> out;

    unsigned long width, height;

    //read in the image file contents to a buffer
    if(IOManager::readFileToBuffer(filePath, in) == false)
      fatalError("Failed to load PNG to buffer")

    //decode the .png format into an array of pixels
    int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
    if(errorCode != 0)
      fatalError("decodePNG failed with error " + std::to_string(errorCode));

    glGenTextures(1, &(texture.id));

    glBindTexture(GL_TEXTURE_2D, texture.id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    texture.width = width;
    texture.height = height;

    return texture;
  }

}
