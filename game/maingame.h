#ifndef MAINGAME_H
#define MAINGAME_H

#include "../engine/window.h"
#include "../engine/glslprogram.h"
#include "../engine/camera2d.h"
#include "../engine/inputmanager.h"
#include "level.h"

enum class GameState {
  PLAY,
  EXIT
};

class MainGame {
public:
  MainGame();
  ~MainGame();

  void run();

private:

  void initSystems();

  void initLevel();

  void initShaders();

  void gameLoop();

  void updateAgents();

  void updateBullets();

  void checkVictory();

  void processInput();

  void drawGame();

  Engine::Window _window;

  Engine::GLSLProgram _textureProgram;

  Engine::InputManager _inputManager;

  Engine::Camera2D _camera;

  std::vector<Level*> _levels; //vector of all levels

  int _screenWidth, _screenHeight;

  int _fps;

  int _currentLevel;

  GameState _gameState;
};



#endif
