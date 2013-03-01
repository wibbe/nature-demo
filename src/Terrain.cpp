
#include "Terrain.h"

#include <vector>
#include <cassert>
#include "gameplay.h"

inline float clamp(float x, float a, float b)
{
    return x < a ? a : (x > b ? b : x);
}

inline void add2(std::vector<float> & v, float x, float y)
{
  v.push_back(x);
  v.push_back(y);
}

inline void add3(std::vector<float> & v, float x, float y, float z)
{
  v.push_back(x);
  v.push_back(y);
  v.push_back(z);
}

gameplay::Mesh * createHexMesh(int resolutionX, int resolutionY, float width, float height)
{
  using namespace gameplay;

  std::vector<float> vertices;

  float halfWidth = width / 2.0f;
  float halfHeight = height / 2.0f;

  for (int x = 0; x < resolutionX; ++x)
  {
    float x1 = clamp((x - 0.5f) / resolutionX, 0.0f, 1.0f);
    float x2 = clamp((x + 0.0f) / resolutionX, 0.0f, 1.0f);
    float x3 = clamp((x + 0.5f) / resolutionX, 0.0f, 1.0f);
    float x4 = clamp((x + 1.0f) / resolutionX, 0.0f, 1.0f);

    for (int y = 0; y < resolutionY; y += 2)
    {
      float t = (y + 0.0f) / resolutionY;
      float m = (y + 1.0f) / resolutionY;
      float b = (y + 2.0f) / resolutionY;

      add2(vertices, x1 * width - halfWidth, t * height - halfHeight);
      add2(vertices, x1, t);
      add3(vertices, 1, 0, 0);

      add2(vertices, x3 * width - halfWidth, t * height - halfHeight);
      add2(vertices, x3, t);
      add3(vertices, 0, 1, 0);

      add2(vertices, x2 * width - halfWidth, m * height - halfHeight);
      add2(vertices, x2, m);
      add3(vertices, 0, 0, 1);

      add2(vertices, x2 * width - halfWidth, m * height - halfHeight);
      add2(vertices, x2, m);
      add3(vertices, 1, 0, 0);

      add2(vertices, x3 * width - halfWidth, t * height - halfHeight);
      add2(vertices, x3, t);
      add3(vertices, 0, 1, 0);

      add2(vertices, x4 * width - halfWidth, m * height - halfHeight);
      add2(vertices, x4, m);
      add3(vertices, 0, 0, 1);

      add2(vertices, x1 * width - halfWidth, b * height - halfHeight);
      add2(vertices, x1, b);
      add3(vertices, 1, 0, 0);

      add2(vertices, x2 * width - halfWidth, m * height - halfHeight);
      add2(vertices, x2, m);
      add3(vertices, 0, 1, 0);

      add2(vertices, x3 * width - halfWidth, b * height - halfHeight);
      add2(vertices, x3, b);
      add3(vertices, 0, 0, 1);

      add2(vertices, x2 * width - halfWidth, m * height - halfHeight);
      add2(vertices, x2, m);
      add3(vertices, 1, 0, 0);

      add2(vertices, x4 * width - halfWidth, m * height - halfHeight);
      add2(vertices, x4, m);
      add3(vertices, 0, 1, 0);

      add2(vertices, x3 * width - halfWidth, b * height - halfHeight);
      add2(vertices, x3, b);
      add3(vertices, 0, 0, 1);
    }
  }

  VertexFormat::Element elements[] = {
    VertexFormat::Element(VertexFormat::POSITION, 2),
    VertexFormat::Element(VertexFormat::TEXCOORD0, 2),
    VertexFormat::Element(VertexFormat::TEXCOORD1, 3)
  };

  Mesh * mesh = Mesh::createMesh(VertexFormat(elements, 3), vertices.size() / 7, false);
  mesh->setPrimitiveType(Mesh::TRIANGLES);
  mesh->setVertexData(&vertices[0], 0, vertices.size() / 7);

  return mesh;
}

Terrain::Terrain(int resolutionX, int resolutionY)
{
  using namespace gameplay;

  _heights = new Processor(resolutionX, resolutionY);
  _normals = new Processor(resolutionX, resolutionY);
  _occlusions = new Processor(resolutionX, resolutionY);

  _hexGrid = gameplay::Model::create(createHexMesh(resolutionX, resolutionY, 1.0f, 1.0f));
  Material * material = _hexGrid->setMaterial("res/terrain.material");

  Texture::Sampler * sampler = Texture::Sampler::create(_heights->result());
  sampler->setWrapMode(Texture::CLAMP, Texture::CLAMP);
  material->getTechnique("display")->getPass("display")->getParameter("heights")->setValue(sampler);

  sampler = Texture::Sampler::create(_normals->result());
  sampler->setWrapMode(Texture::CLAMP, Texture::CLAMP);
  material->getTechnique("display")->getPass("display")->getParameter("normals")->setValue(sampler);

  Material * simulation = Material::create("res/simulation.material");

  _generateHeightmap = Processor::getPass(simulation, "generator", "simplex");
  _calculateNormals = Processor::getPass(simulation, "terrain", "calculate-normals");
  _calculateNormals->getParameter("pixelScale")->setValue(1.0f / resolutionX);
  _calculateNormals->getParameter("heights")->setValue(Texture::Sampler::create(_heights->result()));

  _heights->run(_generateHeightmap);
}

void Terrain::update()
{
  _normals->run(_calculateNormals);
}

void Terrain::draw()
{
  _hexGrid->draw();
}