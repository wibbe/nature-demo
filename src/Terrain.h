
#pragma once

#include "Processor.h"

namespace gameplay {
  class Model;
  class VertexAttributeBinding;
  class Pass;
}

class Terrain
{
  public:
    Terrain(int resolutionX, int resolutionZ);

    void update();
    void draw(const char * technique);

    gameplay::Model * model() const { return _hexGrid; }

    Processor * heights() const { return _heights; }

  private:
    Processor * _heights;
    Processor * _normals;
    Processor * _occlusions;

    gameplay::Pass * _generateHeightmap;
    gameplay::Pass * _calculateNormals;

    gameplay::Model * _hexGrid;
};
