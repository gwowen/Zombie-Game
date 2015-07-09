#include "maingame.h"

#include "../engine/engine.h"
#include "../engine/timing.h"

#include <SDL2/SDL.h>
#include <iostream>

MainGame::MainGame() :
  _screenWidth(1024),
  _screenHeight(768),
  _gameState(GameState::PLAY),
  _fps(0),
  _player(nullptr)
{

}

MainGame::~MainGame() {

  for(int i = 0; i < _levels.size(); ++i)
    delete _levels[i];

}

void MainGame::run() {
  initSystems();
  initLevel();
  gameLoop();

}

void MainGame::initSystems() {
  Engine::init();

  _window.create("Zombie Game", _screenWidth, _screenHeight, 0);

  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

  initShaders();

  _agentSpriteBatch.init();

  _camera.init(_screenWidth, _screenHeight);

}




void MainGame::initLevel() {
  _levels.push_back(new Level("../../game/Levels/level1.txt"));

  _currentLevel = 0;

  _player = new Player();
  _player->init(1.0f, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager);

  _humans.push_back(_player);
}


void MainGame::initShaders() {
  _textureProgram.compileShaders("../../game/Shaders/textureShaderVert.glsl", "../../game/Shaders/textureShaderFrag.glsl");
  _textureProgram.addAttribute("vertexPosition");
  _textureProgram.addAttribute("vertexColor");
  _textureProgram.addAttribute("vertexUV");
  _textureProgram.linkShaders();
}

void MainGame::gameLoop() {

  Engine::fpsLimiter fpsLimiter;
  fpsLimiter.setMaxFPS(60.0f);

  while(_gameState == GameState::PLAY) {

    fpsLimiter.begin();

    processInput();

    _camera.setPosition(_player->getPosition());
    _camera.update();
    drawGame();
    _fps = fpsLimiter.end();

  }
}


void MainGame::updateAgents() {
  for(int i = 0; i < _humans.size(); ++i) {
    _humans[i]->update();
  }

  //don't forget to update zombies!
}

void MainGame::processInput() {

  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_QUIT:
          _gameState = GameState::EXIT;
        break;
      case SDL_MOUSEMOTION:
        _inputManager.setMouseCoords(event.motion.x, event.motion.y);
        break;
      case SDL_KEYDOWN:
        _inputManager.pressKey(event.key.keysym.sym);
        break;
      case SDL_KEYUP:
        _inputManager.pressKey(event.button.button);
        break;
      case SDL_MOUSEBUTTONDOWN:
        _inputManager.pressKey(event.button.button);
        break;
      case SDL_MOUSEBUTTONUP:
        _inputManager.releaseKey(event.button.button);
        break;
    }
  }
}

void MainGame::drawGame() {
  glClearDepth(1.0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _textureProgram.use();

  //make sure the game uses texture unit 0
  glActiveTexture(GL_TEXTURE0);
  GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
  glUniform1i(textureUniform, 0);

  //grab the camera matrix
  glm::mat4 projectionMatrix = _camera.getCameraMatrix();
  GLint pUniform = _textureProgram.getUniformLocation("P");
  glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

  //draw the level
  _levels[_currentLevel]->draw();


  //begin drawing agents
  _agentSpriteBatch.begin();

  //draw the humans
  for(int i = 0; i < _humans.size(); ++i) {
    _humans[i]->draw(_agentSpriteBatch);
  }

  _agentSpriteBatch.end();

  _agentSpriteBatch.renderBatch();

  _textureProgram.unuse();

  _window.swapBuffer();
}
