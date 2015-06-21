#ifndef IOMANAGER_H
#define IOMANAGER_H


namespace Engine {
  class IOManager
  {
  public:
    static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
  };
}

#endif
