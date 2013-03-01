#include "NatureGame.h"

// Declare our game instance
NatureGame game;

NatureGame::NatureGame()
    : _scene(NULL)
{
  _movement.forward = false;
  _movement.backward = false;
  _movement.strafeLeft = false;
  _movement.strafeRight = false;
}

void NatureGame::initialize()
{
  // Load game scene from file
  gameplay::Bundle * bundle = gameplay::Bundle::create("res/box.gpb");
  _scene = bundle->loadScene();
  SAFE_RELEASE(bundle);

  _camera = gameplay::Camera::createPerspective(60, (float)getWidth() / (float)getHeight(), 0.1, 1000.0);

  _cameraNode = _scene->addNode("camera");
  _cameraNode->setTranslation(gameplay::Vector3(0, 5, 10));
  _cameraPitch = gameplay::Node::create("pitch");
  _cameraNode->addChild(_cameraPitch);
  _cameraPitch->setCamera(_camera);

  _scene->setActiveCamera(_camera);

  // Get light node
  gameplay::Node* lightNode = _scene->findNode("directionalLight");
  gameplay::Light* light = lightNode->getLight();

  // Initialize box model
  gameplay::Node* boxNode = _scene->findNode("box");
  gameplay::Model* boxModel = boxNode->getModel();
  gameplay::Material* boxMaterial = boxModel->setMaterial("res/box.material");
  boxMaterial->getParameter("u_ambientColor")->setValue(_scene->getAmbientColor());
  boxMaterial->getParameter("u_lightColor")->setValue(light->getColor());
  boxMaterial->getParameter("u_lightDirection")->setValue(lightNode->getForwardVectorView());

  _terrain = new Terrain(512, 512);
  _scene->addNode("terrain")->setModel(_terrain->model());
}

void NatureGame::finalize()
{
    SAFE_RELEASE(_scene);
}

void NatureGame::update(float elapsedTime)
{
    // Rotate model
  _scene->findNode("box")->rotateY(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));
  _terrain->update();

  if (_movement.forward || _movement.backward)
  {
    float amount = ((_movement.forward ? 1.0f : 0.0f) + (_movement.backward ? -1.0f : 0.0f)) * elapsedTime * 0.01f;
    gameplay::Vector3 dir = _cameraPitch->getForwardVectorWorld();
    dir.normalize().scale(amount);
    _cameraNode->translate(dir);
  }

  if (_movement.strafeLeft || _movement.strafeRight)
  {
    float amount = ((_movement.strafeLeft ? 1.0f : 0.0f) + (_movement.strafeRight ? -1.0f : 0.0f)) * elapsedTime * 0.006f;
    _cameraNode->translateLeft(amount);
  }
}

void NatureGame::render(float elapsedTime)
{
  setViewport(getViewport());
  GL_ASSERT( glClearColor(0.2, 0.4, 0.9, 1.0) );

  // Clear the color and depth buffers
  clear(CLEAR_COLOR_DEPTH, gameplay::Vector4::zero(), 1.0f, 0);

  // Visit all the nodes in the scene for drawing
  //_scene->visit(this, &NatureGame::drawScene);

  _terrain->draw();
}

bool NatureGame::drawScene(gameplay::Node* node)
{
  // If the node visited contains a model, draw it
  gameplay::Model* model = node->getModel();
  if (model)
  {
      model->draw();
  }
  return true;
}

void NatureGame::keyEvent(gameplay::Keyboard::KeyEvent evt, int key)
{
  if (evt == gameplay::Keyboard::KEY_PRESS)
  {
    switch (key)
    {
      case gameplay::Keyboard::KEY_ESCAPE:
        exit();
        break;

      case gameplay::Keyboard::KEY_W:
        _movement.forward = true;
        break;

      case gameplay::Keyboard::KEY_S:
        _movement.backward = true;
        break;

      case gameplay::Keyboard::KEY_A:
        _movement.strafeLeft = true;
        break;

      case gameplay::Keyboard::KEY_D:
        _movement.strafeRight = true;
        break;
    }
  }
  else if (evt == gameplay::Keyboard::KEY_RELEASE)
  {
    switch (key)
    {
      case gameplay::Keyboard::KEY_W:
        _movement.forward = false;
        break;

      case gameplay::Keyboard::KEY_S:
        _movement.backward = false;
        break;

      case gameplay::Keyboard::KEY_A:
        _movement.strafeLeft = false;
        break;

      case gameplay::Keyboard::KEY_D:
        _movement.strafeRight = false;
        break;
    }
  }
}

bool NatureGame::mouseEvent(gameplay::Mouse::MouseEvent evt, int x, int y, int wheelDelta)
{
  switch (evt)
  {
    case gameplay::Mouse::MOUSE_PRESS_RIGHT_BUTTON:
      _movement.mouseDown = true;
      _movement.mouseX = x;
      _movement.mouseY = y;
      break;

    case gameplay::Mouse::MOUSE_RELEASE_RIGHT_BUTTON:
      _movement.mouseDown = false;
      break;

    case gameplay::Mouse::MOUSE_MOVE:
      if (_movement.mouseDown)
      {
        int diffX = x - _movement.mouseX;
        int diffY = y - _movement.mouseY;
        _movement.mouseX = x;
        _movement.mouseY = y;

        float yaw = diffX * 0.002f;
        float pitch = diffY * 0.002f;

        _cameraNode->rotateY(-yaw);
        _cameraPitch->rotateX(-pitch);
      }
      break;
  }
}
