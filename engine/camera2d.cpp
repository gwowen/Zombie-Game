#include "camera2d.h"

namespace Engine {

    Camera2D::Camera2D() : _position(0.0f, 0.0f),
    _cameraMatrix(1.0f),
    _orthoMatrix(1.0f),
    _scale(1.0f),
    _needsMatrixUpdate(true),
    _screenWidth(500),
    _screenHeight(500)
    {

    }

    Camera2D::~Camera2D()
    {

    }

    void Camera2D::init(int screenWidth, int screenHeight) {
        _screenWidth = screenWidth;
        _screenHeight = screenHeight;
        _orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
    }

    void Camera2D::update() {

      //only update if our position or scale have changed
      if(_needsMatrixUpdate) {

        //camera translation
        glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
        _cameraMatrix = glm::translate(_orthoMatrix, translate);

        //camera scale
        glm::vec3 scale(_scale, _scale, 0.0f);
        _cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

        _needsMatrixUpdate = false;
      }
    }

    glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {
      //invert y direction
      screenCoords.y = _screenHeight - screenCoords.y;
      //make it so that 0 is the center
      screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
      //scale the coordinates
      screenCoords /= _scale;
      //translate with the camera position
      screenCoords += _position;
      return screenCoords;
    }

}
