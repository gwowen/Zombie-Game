#include "maingame.h"

#include "../engine/engine.h"

#include <SDL2/SDL.h>
#include <iostream>

MainGame::MainGame() :
  _screenWidth(1024),
  _screenHeight(768)

{

}

MainGame::~MainGame() {

  for(int i = 0; i < _levels.size(); ++i)
    delete _levels[i];

}

void MainGame::run() {
  _levels.push_back(new Level("../../game/Levels/level1.txt"));

}

void MainGame::initSystems() {
  Engine::init();

  _window.create("Zombie Game", _screenWidth, _screenHeight, 0);

  initShaders();

  _levels.push_back(new Level("../../game/Levels/level1.txt"));


}

void MainGame::initShaders() {
  _textureProgram.compileShaders("../../game/Shaders/textureShaderVert.glsl", "../../game/Shaders/textureShaderFrag.glsl");
  _textureProgram.addAttribute("vertexPosition");
  _textureProgram.addAttribute("vertexColor");
  _textureProgram.addAttribute("vertexUV");
  _textureProgram.linkShaders();
}

void MainGame::gameLoop() {

}

void MainGame::processInput() {

  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_QUIT:

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

  _window.swapBuffer();
}
