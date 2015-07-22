#include "maingame.h"

#include "../engine/engine.h"
#include "../engine/timing.h"
#include "../engine/errors.h"


#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <ctime>

#include "zombie.h"
#include "gun.h"



const float HUMAN_SPEED = 1.0f;
const float PLAYER_SPEED = 5.0f;
const float ZOMBIE_SPEED = 1.3f;

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

  for(int i = 0; i <_humans.size(); ++i)
    delete _humans[i];

  for(int i = 0; i < _zombies.size(); ++i)
    delete _zombies[i];

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
  _player->init(PLAYER_SPEED, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager, &_camera, &_bullets);

  _humans.push_back(_player);

  std::mt19937 randomEngine;
  randomEngine.seed(time(nullptr));

  std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->getWidth() - 2);
  std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() - 2);

  //add in all humans, randomly
  for(int i = 0; i < _levels[_currentLevel]->getNumHumans(); ++i) {
    _humans.push_back(new Human);
    glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
    _humans.back()->init(HUMAN_SPEED, pos);
  }


  //add zombies
  const std::vector<glm::vec2>& zombiePositions = _levels[_currentLevel]->getZombieStartPositions();
  for(int i = 0; i < zombiePositions.size(); ++i) {
    _zombies.push_back(new Zombie);
    _zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
  }

  const float BULLET_SPEED = 20.0f;
  _player->addGun(new Gun("Magnum", 10, 1, 5.0f, 30, BULLET_SPEED));
  _player->addGun(new Gun("Shotgun", 30, 12, 20.0f, 4, BULLET_SPEED));
  _player->addGun(new Gun("MP5", 2, 1, 10.0f, 20, BULLET_SPEED));
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

    updateAgents();

    updateBullets();

    _camera.setPosition(_player->getPosition());

    _camera.update();

    drawGame();

    _fps = fpsLimiter.end();
  }
}


void MainGame::updateAgents() {
  //update humans
  for(int i = 0; i < _humans.size(); ++i) {
    _humans[i]->update(_levels[_currentLevel]->getLevelData(),
                      _humans,
                      _zombies);
  }

  //update zombies
  for(int i = 0; i < _zombies.size(); ++i) {
    _zombies[i]->update(_levels[_currentLevel]->getLevelData(),
                      _humans,
                      _zombies);
  }

  //update zombie collisions
  for(int i = 0; i < _zombies.size(); ++i) {
    //collide with other zombies
    for(int j = i + 1; j < _zombies.size(); ++j) {
      _zombies[i]->collideWithAgent(_zombies[j]);
    }
    //collide with humans
    for(int j = 1; j < _humans.size(); ++j) {
      if(_zombies[i]->collideWithAgent(_humans[j])) {
        //add the new zombie
        _zombies.push_back(new Zombie);
        _zombies.back()->init(ZOMBIE_SPEED, _humans[j]->getPosition());
        //delete the human
        delete _humans[j];
        _humans[j] = _humans.back();
        _humans.pop_back();
      }
    }

  //collide with player
    if(_zombies[i]->collideWithAgent(_player)) {
        Engine::fatalError("You lose!");
      }
  }

  //update human collisions
  for(int i = 0; i < _humans.size(); ++i) {
    for(int j = i + 1; j < _humans.size(); ++j) {
      _humans[i]->collideWithAgent(_humans[j]);
    }
  }
}

void MainGame::updateBullets() {
  //update and collide with wordl
  for(int i = 0; i < _bullets.size(); ) {
    //if update returns true, bullet collided with a wall
    if(_bullets[i].update(_levels[_currentLevel]->getLevelData())) {
      _bullets[i] = _bullets.back();
      _bullets.pop_back();
    } else {
      ++i;
    }
  }

  bool wasBulletRemoved;

  //collide with humans and zombies
  for(int i =0; i < _bullets.size(); ++i) {
    wasBulletRemoved = false;
    //loop through zombies
    for(int j = 0; j < _zombies.size(); ) {
      //check collision
      if(_bullets[i].collideWithAgent(_zombies[j])) {
        //damage zombie and kill it if it's out of health
        if(_zombies[j]->applyDamage(_bullets[i].getDamage())) {
          //if the zombie died remove it
          delete _zombies[j];
          _zombies[j] = _zombies.back();
          _zombies.pop_back();
          ++_numZombiesKilled;
        } else {
          ++j;
        }

        //remove the bullet
        _bullets[i] = _bullets.back();
        _bullets.pop_back();
        wasBulletRemoved = true;
        --i;
        break;
      } else {
        ++j;
      }
    }

    //loop through humans
    if(wasBulletRemoved == false) {
      for(int j = 1; j < _humans.size(); ) {
        //check collision
        if(_bullets[i].collideWithAgent(_humans[j])) {
          if(_humans[j]->applyDamage(_bullets[i].getDamage())) {
          //if the human died, remove it
          delete _humans[j];
          _humans[j] = _humans.back();
          _humans.pop_back();
        } else {
          ++j;
        }

        //remove the bullets
        _bullets[i] = _bullets.back();
        _bullets.pop_back();
        ++_numHumansKilled;
        --i;
        break;
      } else {
        ++j;
        }
      }
    }
  }
}

void MainGame::checkVictory() {
  if(_zombies.empty()) {
    std::printf("*** You win! ***\n You killed %d humans and %d zombies. There are  %d/%d civilians remaining",
                _numHumansKilled, _numZombiesKilled, _humans.size() - 1, _levels[_currentLevel]->getNumHumans());
    Engine::fatalError("");
  }
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
        _inputManager.releaseKey(event.key.keysym.sym);
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

  //draw the zombies
  for(int i = 0; i < _zombies.size(); ++i) {
    _zombies[i]->draw(_agentSpriteBatch);
  }

  for(int i = 0; i < _bullets.size(); ++i) {
    _bullets[i].draw(_agentSpriteBatch);
  }




  _agentSpriteBatch.end();

  _agentSpriteBatch.renderBatch();

  _textureProgram.unuse();

  _window.swapBuffer();
}
