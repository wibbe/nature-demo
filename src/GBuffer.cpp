
#include "GBuffer.h"

#include "Base.h"
#include "FrameBuffer.h"
#include "RenderTarget.h"
#include "Texture.h"
#include "DepthStencilTarget.h"

using namespace gameplay;

extern uint32_t createFloatTexture(int width, int height);

GBuffer::GBuffer(int width, int height)
  : _width(width),
    _height(height),
    _fbo(0),
    _albedo(0),
    _position(0)
{
  assert(FrameBuffer::getMaxRenderTargets() >= 2);

  _fbo = FrameBuffer::create("GBuffer");

  _albedo = Texture::create(createFloatTexture(width, height), width, height);
  _position = Texture::create(createFloatTexture(width, height), width, height);
  DepthStencilTarget * depthStencil = DepthStencilTarget::create("DepthBuffer", DepthStencilTarget::DEPTH, width, height);

  _fbo->setRenderTarget(RenderTarget::create("albedo", _albedo), 0);
  _fbo->setRenderTarget(RenderTarget::create("position", _position), 1);
  _fbo->setDepthStencilTarget(depthStencil);
}

GBuffer::~GBuffer()
{
}

gameplay::FrameBuffer * GBuffer::bind()
{
  return _fbo->bind();
}