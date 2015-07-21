#ifndef MAINGAME_H
#define MAINGAME_H

#include "../engine/window.h"
#include "../engine/glslprogram.h"
#include "../engine/camera2d.h"
#include "../engine/inputmanager.h"
#include "../engine/spritebatch.h"

#include "player.h"
#include "level.h"
#include "bullet.h"

class Zombie;

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

  //update all agents
  void updateAgents();

  void updateBullets();

  void checkVictory();

  void processInput();

  void drawGame();


  //member variables

  Engine::Window _window;

  Engine::GLSLProgram _textureProgram;

  Engine::InputManager _inputManager;

  Engine::Camera2D _camera; //main Camera

  Engine::SpriteBatch _agentSpriteBatch; //draws all agents

  std::vector<Level*> _levels; //vector of all levels

  int _screenWidth, _screenHeight;

  float _fps;

  int _currentLevel;

  Player* _player;

  std::vector<Human*> _humans;

  std::vector<Zombie*> _zombies;

  std::vector<Bullet> _bullets;

  int _numHumansKilled;
  int _numZombiesKilled;

  GameState _gameState;
};



#endif
