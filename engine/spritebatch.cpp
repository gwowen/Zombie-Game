#include "spritebatch.h"
#include <algorithm>

namespace Engine {

  SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
  {

  }

  SpriteBatch::~SpriteBatch()
  {

  }

  void SpriteBatch::init() {
    createVertexArray();
  }

  void SpriteBatch::begin(GlyphSortType sortType /*GlyphSortType::Texture*/) {
    _sortType = sortType;
    _renderBatches.clear();
    //delete any remaining glyphs to avoid memory leaks!
    for(int i = 0; i < _glyphs.size(); ++i)
      delete _glyphs[i];

    _glyphs.clear();
  }

  void SpriteBatch::end() {
    sortGlyphs();
    createRenderBatches();
  }

  void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture,
                          float depth, const Color& color) {

    Glyph* newGlyph = new Glyph;
    newGlyph->texture = texture;
    newGlyph->depth = depth;

    newGlyph->topLeft.color = color;
    newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
    newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

    newGlyph->bottomLeft.color = color;
    newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
    newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

    newGlyph->bottomRight.color = color;
    newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
    newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

    newGlyph->topRight.color = color;
    newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y +destRect.w);
    newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

    _glyphs.push_back(newGlyph);
  }

  void SpriteBatch::renderBatch() {

    //bind our VAO, textures and then draw
    glBindVertexArray(_vao);

    for(int i = 0; i < _renderBatches.size(); ++i) {
      glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
      glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, renderBatches[i].numVertices)
    }

    glBindVertexArray(0);
  }

  void SpriteBatch::createRenderBatches() {
    //this will store all the vertices that need uploading
    std::vector<Vertex> vertices;
    //resize the buffer to the exact size we need so as to treat
    //it as an array
    vertices.resize(_glyphs.size() * 6);

    if(_glyphs.empty())
      return;

    int offset = 0; //current offset
    int vertex = 0; //current vertex

    //add the first batch
    _renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
    vertices[cv++] = _glyphs[0]->topLeft;
    vertices[cv++] = _glyphs[0]->bottomLeft;
    vertices[cv++] = _glyphs[0]->bottomRight;
    vertices[cv++] = _glyphs[0]->bottomRight;
    vertices[cv++] = _glyphs[0]->topRight;
    vertices[cv++] = _glyphs[0]->topLeft;
    offset += 6;

    //add all the rest of the glyphs
    for(int cg = 1; cg < _glyphs.size(); ++cg) {

      //check if this glyph can be part of the current batch
      if(_glyphs[cg]->texture != _glyphs[cg - 1]->texture) {
        //make a new batch
        _renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
      } else {
        //if it's part of the current batch, just increase numVertices
        _renderBatches.back().numVertices += 6;
      }
      vertices[cv++] = _glyphs[cg]->topLeft;
      vertices[cv++] = _glyphs[cg]->bottomLeft;
      vertices[cv++] = _glyphs[cg]->bottomRight;
      vertices[cv++] = _glyphs[cg]->bottomRight;
      vertices[cv++] = _glyphs[cg]->topRight;
      vertices[cv++] = _glyphs[cg]->topLeft;
      offset += 6;
    }

    //bind our vbo
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    //orphan the buffer (for speed)
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
    //uploade the data
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void SpriteBatch::createVertexArray() {
    //generate the VAO if it isn't already generated
    if(_vao == 0)
      glGenVertexArrays(1, &_vao);

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glEnableVertexAttribArrays(0);
    glEnableVertexAttribArrays(1);
    glEnableVertexAttribArrays(2);

    //this is the position attribute pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    //this is the color attribute pointer
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    //this is the UV attribute pointer
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindVertexArray(0);

  }

  void SpriteBatch::sortGlyphs() {

    switch(_sortType) {
      case GlyphSortType::BACK_TO_FRONT:
        std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
        break;
      case GlyphSortType::FRONT_TO_BACK:
        std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
        break;
      case GlyphSortType::TEXTURE:
        std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
        break;
    }
  }

  bool SpriteBatch::compateFrontToBack(Glyph* a, Glyph *b) {
    return (a->depth < b->depth);
  }

  bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b) {
    return (a->depth > b->depth);
  }

  bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) {
    return (a->texture < b->texture);
  }

}
