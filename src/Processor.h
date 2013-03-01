
#pragma once

#include "Base.h"
#include "RenderState.h"

namespace gameplay {
  class Texture;
  class FrameBuffer;
  class Mesh;
  class Effect;
  class VertexAttributeBinding;
  class Material;
  class Pass;
}

class Processor
{
  public:
    Processor(int width, int height);
    void run(gameplay::Pass * pass);

    gameplay::Texture * result() const { return _result; }

    static gameplay::Mesh * screenMesh() { return _screenQuad; }

    static gameplay::Pass * getPass(gameplay::Material * material, const char * technique, const char * pass);

  private:
    gameplay::FrameBuffer * _fbo;
    gameplay::Texture * _result;

    static gameplay::Mesh * _screenQuad;
};