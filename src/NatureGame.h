#ifndef TEMPLATEGAME_H_
#define TEMPLATEGAME_H_

#include "gameplay.h"

#include "Terrain.h"
#include "GBuffer.h"

/**
 * Main game class.
 */
class NatureGame: public gameplay::Game
{
  public:
    NatureGame();

	  void keyEvent(gameplay::Keyboard::KeyEvent evt, int key);
    bool mouseEvent(gameplay::Mouse::MouseEvent evt, int x, int y, int wheelDelta);

  protected:
    void initialize();

    /**
     * @see Game::finalize
     */
    void finalize();

    /**
     * @see Game::update
     */
    void update(float elapsedTime);

    /**
     * @see Game::render
     */
    void render(float elapsedTime);

  private:
    void drawScene(const char * technique);
    bool drawNode(gameplay::Node* node);

  private:
    gameplay::Scene * _scene;
    gameplay::Camera * _camera;
    gameplay::Node * _cameraNode;
    gameplay::Node * _cameraPitch;

    gameplay::SpriteBatch * _albedoBatch;
    gameplay::SpriteBatch * _positionBatch;

    GBuffer * _gbuffer;
    Terrain * _terrain;

    struct Movement {
      bool forward;
      bool backward;
      bool strafeLeft;
      bool strafeRight;
      bool mouseDown;
      int mouseX, mouseY;
    } _movement;
};

#endif
