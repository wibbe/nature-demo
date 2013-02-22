
#include "Processor.h"

#include "Base.h"
#include "FrameBuffer.h"
#include "RenderTarget.h"
#include "Texture.h"
#include "Mesh.h"
#include "Effect.h"

using namespace gameplay;

static uint32_t createFloatTexture(int width, int height)
{
  uint32_t textureId;
  GL_ASSERT( glGenTextures(1, &textureId) );
  GL_ASSERT( glBindTexture(GL_TEXTURE_2D, textureId) );
  GL_ASSERT( glPixelStorei(GL_UNPACK_ALIGNMENT, 1) );
  GL_ASSERT( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, 0) );
  GL_ASSERT( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
  GL_ASSERT( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );

  return textureId;
}

Mesh * Processor::_screenQuad = 0;

Processor::Processor(int width, int height)
{
  _result = Texture::create(createFloatTexture(width, height), width, height);
  _fbo = FrameBuffer::create("processor", width, height);
  _fbo->setRenderTarget(RenderTarget::create("processor", _result));

  if (!_screenQuad)
    _screenQuad = Mesh::createQuadFullscreen();
}

void Processor::run(Effect * effect)
{
  GL_ASSERT( glClearColor(0.0, 0.0, 0.0, 0.0) );
  GL_ASSERT( glClear(GL_COLOR_BUFFER_BIT) );
  effect->bind();
  GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
  GL_ASSERT( glDrawArrays(_screenQuad->getPrimitiveType(), 0, _screenQuad->getVertexCount()) );
}