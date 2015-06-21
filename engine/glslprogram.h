#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <string>
#include <GL/glew.h>

namespace Engine {

  class GLSLProgram
  {
  public:
    GLSLProgram();
    ~GLSLProgram();

    void compileShaders( const std::string& vertexShaderFilepath, const std::string& fragmentShaderFilepath);

    void linkShaders();

    void addAttribute(const std::string& attributeName);

    GLint getUniformLocation(const std::string& uniformName);
    void use();
    void unuse();

  private:
    int _numAttributes;

    void compileShader(const std::string& filePath, GLuint id);

    GLuint _programID;
    GLuint _vertexShaderID;
    GLuint _fragmentShaderID;
  };

}

#endif
