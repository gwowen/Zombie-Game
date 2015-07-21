#include "agent.h"
#include "../engine/resourcemanager.h"
#include "level.h"

Agent::Agent()
{

}

Agent::~Agent()
{

}

bool Agent::collideWithLevel(const std::vector<std::string>& levelData) {

  std::vector<glm::vec2> collideTilePositions;

  //first corner
  checkTilePosition(levelData,
                    collideTilePositions,
                    _position.x,
                    _position.y);
  //second corner
  checkTilePosition(levelData,
                   collideTilePositions,
                   _position.x + AGENT_WIDTH,
                   _position.y);
 //third corner
 checkTilePosition(levelData,
                  collideTilePositions,
                  _position.x + AGENT_WIDTH,
                  _position.y + AGENT_WIDTH);

  //check if there was no collision
  if(collideTilePositions.size() == 0) {
    return false;
  }

  //do the collision
 for(int i = 0; i < collideTilePositions.size(); ++i) {
    collideWithTile(collideTilePositions[i]);
  }

  return true;
}

//circular collision
bool Agent::collideWithAgent(Agent* agent) {

}

void Agent::draw(Engine::SpriteBatch& _spriteBatch) {

    static int textureID = Engine::ResourceManager::getTexture("../../game/Textures/circle.png").id;

    const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

    glm::vec4 destRect;
    destRect.x = _position.x;
    destRect.y = _position.y;
    destRect.z = AGENT_WIDTH;
    destRect.w = AGENT_WIDTH;

    _spriteBatch.draw(destRect, uvRect, textureID, 0.0f, _color);

}

bool Agent::applyDamage(float damage) {

  _health -= damage;
  //if we died, return true
  if(_health <= 0) {
    return true;
  }

  return false;

}

void Agent::checkTilePosition(const std::vector<std::string>& levelData,
                              std::vector<glm::vec2>& collideTilePositions,
                              float x,
                              float y) {

      //get the position of the tile in grid-space
      glm::vec2 gridPos = glm::vec2(floor(x / (float)TILE_WIDTH),
                                    floor(y / (float)TILE_WIDTH));

    //if we're outside the world, just return
    if( gridPos.x < 0 || gridPos.x >= levelData[0].size() ||
        gridPos.y < 0 || gridPos.y >= levelData.size()) {
          return;
        }

    //check we're not colliding with an air tile, else we add it to the collision pile
    if(levelData[gridPos.y][gridPos.x] != '.') {
        collideTilePositions.push_back(gridPos * (float)TILE_WIDTH + glm::vec2((float)(TILE_WIDTH) / 2.0f));
      }
}

//AABB collision
void Agent::collideWithTile(glm::vec2 tilePos) {

  const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
  //the minimum distance before a collision occurs
  const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

  //position of the center of the agent
  glm::vec2 centerAgentPos = _position + glm::vec2(AGENT_RADIUS);
  //vector from the agent to the tile
  glm::vec2 distVec = centerAgentPos - tilePos;

  //check the depth of the collision
  float xDepth = MIN_DISTANCE - std::abs(distVec.x);
  float yDepth = MIN_DISTANCE - std::abs(distVec.y);

  //if either of the depths are > 0, then we have collided
  if(xDepth > 0 && yDepth > 0) {

    //check with collision depth is less
    if(std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
      //x collision depth is smaller so we push in X direction
      if(distVec.x < 0) {
        _position.x -= xDepth;
      } else {
        _position.x += xDepth;
      }
    } else {
      //y collision depth is smaller so we push in Y direction
      if(distVec.y < 0) {
        _position.y -= yDepth;
      } else {
        _position.y += yDepth;
      }
    }
  }
}
