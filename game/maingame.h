#ifndef MAINGAME_H
#define MAINGAME_H

#include <engine/window.h>
#include <engine/glslprogram.h>
#include <engine/camera2d.h>
#include <engine/inputmanager.h>

class MainGame {
public:
  MainGame();
  ~MainGame();

  void run();

private:

  void initSystems();

  void initShaders();

  void gameLoop();

  void processInput();

  void drawGame();

  Engine::Window _window;

  Engine::GLSLProgram _textureProgram;

  Engine::InputManager _inputManager;

  Engine::Camera2D _camera;
};



#endif
