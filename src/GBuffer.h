
#pragma once

namespace gameplay {
  class Texture;
  class FrameBuffer;
}


class GBuffer
{
  public:
    GBuffer(int width, int height);
    ~GBuffer();

    int width() const { return _width; }
    int height() const { return _height; }

    gameplay::FrameBuffer * bind();

    gameplay::Texture * albedo() const { return _albedo; }
    gameplay::Texture * position() const { return _position; }

  private:
    int _width, _height;
    gameplay::FrameBuffer * _fbo;
    gameplay::Texture * _albedo;
    gameplay::Texture * _position;
};