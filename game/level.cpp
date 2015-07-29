#include "level.h"

#include "../engine/errors.h"
#include <fstream>
#include <iostream>
#include "../engine/resourcemanager.h"

Level::Level(const std::string& fileName) {

  std::ifstream file;
  file.open(fileName);

  if(file.fail())
    Engine::fatalError("Failed to open " + fileName);

  //throw away the first string in tmp
  std::string tmp;

  file >> tmp >> _numHumans;

  std::getline(file, tmp); //throw away the rest of the first line

  //read level data
  while(std::getline(file, tmp))
    _levelData.push_back(tmp);


  _spriteBatch.init();
  _spriteBatch.begin();

  //texture coordinates rect
  glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

  Engine::ColorRGBA8 whiteColor;
  whiteColor.r = 255;
  whiteColor.g = 255;
  whiteColor.b = 255;
  whiteColor.a = 255;

  //render all the tiles
  for(int y = 0; y < _levelData.size(); ++y) {
      for(int x = 0; x < _levelData[y].size(); ++x) {
        //grab the tile
        char tile = _levelData[y][x];

        //get the destination rect
        glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

        //process the tile - what color is it?
        switch(tile) {
          case 'B':
          case 'R':
              _spriteBatch.draw(destRect,
                                uvRect,
                                Engine::ResourceManager::getTexture("../../game/Textures/red_bricks.png").id,
                                0.0f,
                                whiteColor);
              break;

          case 'G':
            _spriteBatch.draw(destRect,
                              uvRect,
                              Engine::ResourceManager::getTexture("../../game/Textures/glass.png").id,
                              0.0f,
                              whiteColor);
            break;
          case 'L':
            _spriteBatch.draw(destRect,
                              uvRect,
                              Engine::ResourceManager::getTexture("../../game/Textures/light_bricks.png").id,
                              0.0f,
                              whiteColor);
            break;
          case '@':
            _levelData[y][x] = '.'; //don't collide with an @
            _startPlayerPos.x = x * TILE_WIDTH;
            _startPlayerPos.y = y * TILE_WIDTH;
            break;
          case 'Z':
            _levelData[y][x] = '.'; //so we don't collide with a Z
            _zombieStartPositions.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
            break;
          case '.':
            break;
          default:
            std::printf("Unexpected symbol %c at (%d, %d)", tile, x, y);
            break;
        }
      }
  }

  _spriteBatch.end();

}

Level::~Level() {
}

void Level::draw() {
  _spriteBatch.renderBatch();
}
