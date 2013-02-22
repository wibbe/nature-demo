
#pragma once

namespace gameplay {
  class Texture;
  class FrameBuffer;
  class Mesh;
  class Effect;
}

class Processor
{
  public:
    Processor(int width, int height);
    void run(gameplay::Effect * effect);

    gameplay::Texture * result() const { return _result; }

  private:
    gameplay::FrameBuffer * _fbo;
    gameplay::Texture * _result;

    static gameplay::Mesh * _screenQuad;
};