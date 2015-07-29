#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "vertex.h"

namespace Engine {

  //determines how we should sort the glyphs
  enum class GlyphSortType {
    NONE,
    FRONT_TO_BACK,
    BACK_TO_FRONT,
    TEXTURE
  };

  //A glyph is a single quad, containing the texture and position of
  //objects in the game. We add these to spritebatches via the Draw method
  struct Glyph {
    GLuint texture;
    float depth;

    Vertex topLeft;
    Vertex bottomLeft;
    Vertex topRight;
    Vertex bottomRight;
  };

  //A RenderBatch is used for a single draw call. We create a vector of renderbatches
  //and then go through the vector to draw it to the screen.
  class RenderBatch {
  public:
    RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset),
      numVertices(NumVertices), texture(Texture) {
      }
      GLuint offset;
      GLuint numVertices;
      GLuint texture;
  };

  //SpriteBatch draws things queued up in renderbatches to the screen.
  //come up with a better comment later.
  class SpriteBatch
  {
  public:
    SpriteBatch();
    ~SpriteBatch();

    //initialize the sprite batch
    void init();

    //begins the spritebatch
    void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

    //ends the spritebatch
    void end();

    //adds a glyph to the spritebatch
    void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color);

    //renders the entire spritebatch to the screen
    void renderBatch();

  private:
    //creates all the needed renderbatches
    void createRenderBatches();

    //generates our VAO and VBO
    void createVertexArray();

    //sorts glyphs according to _sortType
    void sortGlyphs();

    //comparators used by sortGlyphs
    static bool compareFrontToBack(Glyph* a, Glyph *b);
    static bool compareBackToFront(Glyph* a, Glyph *b);
    static bool compareTexture(Glyph* a, Glyph* b);

    GLuint _vbo;
    GLuint _vao;

    GlyphSortType _sortType;

    std::vector<Glyph*> _glyphs;
    std::vector<RenderBatch> _renderBatches;
  };
}



#endif
