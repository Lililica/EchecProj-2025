#include "renderOPENGL.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"

#define GLFW_INCLUDE_NONE
#include "../Game/Piece/piece.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

void RenderOpenGL::init() {
  // Initialize the OpenGL manager
  manager.OpenGL_init();

  // Initialize the shaders
  init_shaders();

  // Initialize the objects
  init_object();

  // Initialize the skybox
  skybox.init_Vertex();
  skybox.init_Texture();

  // Initialize the random device
  randomDevice.init(static_cast<unsigned int>(time(nullptr)));
  for (int i = 0; i < 20; ++i) {
    meteorites.push_back(std::nullopt);
  }
}

void RenderOpenGL::init_object() {
  // Load the object
  this->objects = std::vector<Object>(7);
  objects[PieceType::PION].obj_loader(ASSETS_PATH "texture/image.png",
                                      ASSETS_PATH "obj/Pawn.obj");
  objects[PieceType::TOUR].obj_loader(ASSETS_PATH "texture/image.png",
                                      ASSETS_PATH "obj/Rook.obj");
  objects[PieceType::ROI].obj_loader(ASSETS_PATH "texture/image.png",
                                     ASSETS_PATH "obj/King.obj");
  objects[PieceType::DAME].obj_loader(ASSETS_PATH "texture/image.png",
                                      ASSETS_PATH "obj/Queen.obj");
  objects[PieceType::FOU].obj_loader(ASSETS_PATH "texture/image.png",
                                     ASSETS_PATH "obj/Bishop.obj");
  objects[PieceType::CAVALIER].obj_loader(ASSETS_PATH "texture/image.png",
                                          ASSETS_PATH "obj/Knight.obj");
  objects[ObjectType::Case].obj_loader(ASSETS_PATH "texture/image.png",
                                       ASSETS_PATH "obj/case.obj");
  objects[ObjectType::Meteorite].obj_loader(ASSETS_PATH "texture/Asteroid.png",
                                            ASSETS_PATH "obj/Asteroid.obj");
}

void RenderOpenGL::draw_content(Game *&currentGame) {
  /*********************************
   * HERE SHOULD COME THE RENDERING CODE
   *********************************/

  manager.update_window_size();
  ProjMatrix = glm::perspective(glm::radians(70.f),
                                float(manager.getWidth()) / manager.getHeight(),
                                0.1f, 2000.f);

  // Draw the skybox
  draw_skybox();

  /* ------------------------ */
  manageFirstView(currentGame);

  button_action();
  mouse_action(currentGame);

  manager.setShaderLoader(&shaders[ShaderIndices::ShaderObj]);
  manager.getShaderLoader()->useProgram();
  draw_game(currentGame);
}

void RenderOpenGL::button_action() {
  if (glfwGetKey(manager.getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
    trackball.rotateLeft(0.8);

  if (glfwGetKey(manager.getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
    trackball.rotateLeft(-0.8);

  if (glfwGetKey(manager.getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
    trackball.rotateUp(-0.8);

  if (glfwGetKey(manager.getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
    trackball.rotateUp(0.8);

  if (glfwGetKey(manager.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
    trackball.moveFront(-0.7);

  if (glfwGetKey(manager.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
    trackball.moveFront(0.7);
}

void RenderOpenGL::mouse_action(Game *&currentGame) {
  // Mouse section

  double xpos = 0;
  double ypos = 0;
  glfwGetCursorPos(manager.getWindow(), &xpos, &ypos);
  mouse.x = static_cast<int>(xpos);
  mouse.y = static_cast<int>(ypos);

  calcul_mouse_collision_hover(currentGame);

  if (glfwGetMouseButton(manager.getWindow(), GLFW_MOUSE_BUTTON_LEFT) ==
      GLFW_PRESS) {
    if (!mouse.isPressed) {
      // Select a case
      select_case_with_mouse(currentGame);
    }

    if (!mouse.isPressed)
      mouse.isPressed = true;
  }

  else {
    if (mouse.isPressed)
      mouse.isPressed = false;
  }
}

void RenderOpenGL::manageFirstView(Game *&currentGame) {
  if (currentGame->get_first_view()->isFirstPerson) {
    if (!currentGame->get_first_view()->previousPos.has_value()) {
      currentGame->get_first_view()->previousPos =
          trackball.getPosition(); // Save the previous position
    }
    // Save the previous position
    std::pair<int, int> piecePos = currentGame->get_pos_selected_piece();
    trackball.set_to(glm::vec3(piecePos.first * plateau.tailleCase -
                                   (plateau.taille - plateau.tailleCase) / 2.,
                               30,
                               piecePos.second * plateau.tailleCase -
                                   (plateau.taille - plateau.tailleCase) / 2.));
  } else {
    if (currentGame->get_first_view()->previousPos.has_value()) {
      trackball.set_to(currentGame->get_first_view()->previousPos.value());
      currentGame->get_first_view()->previousPos.reset(); // Reset the previous
                                                          // position
    }
  }
}

void RenderOpenGL::calcul_mouse_collision_hover(Game *&currentGame) {
  // Get the ray from the mouse position
  mouse.ray =
      getRayFromMouse(mouse.x, mouse.y, manager.getWidth(), manager.getHeight(),
                      trackball.getViewMatrix(), ProjMatrix);

  mouse.collision.tHit = 10000000;
  for (int y{0}; y < currentGame->getGridSize(); ++y) {
    for (int x{0}; x < currentGame->getGridSize(); ++x) {
      // Get the AABB for the object
      glm::vec3 boxMin =
          glm::vec3(x * plateau.tailleCase - (plateau.taille / 2.), 0,
                    y * plateau.tailleCase - (plateau.taille / 2.)); // AABB min
      glm::vec3 boxMax = glm::vec3(
          x * plateau.tailleCase - (plateau.taille / 2.) + plateau.tailleCase,
          0 + plateau.tailleCase * plateau.rapportHauteur,
          y * plateau.tailleCase - (plateau.taille / 2.) +
              plateau.tailleCase); // AABB max

      glm::vec3 rayOrigin = trackball.getPosition();
      if (rayIntersectsAABB(rayOrigin, mouse.ray, boxMin, boxMax,
                            mouse.collision.tHit)) {
        mouse.collision.xHit = x;
        mouse.collision.yHit = y;
      }
    }
  }
}

void RenderOpenGL::select_case_with_mouse(Game *&currentGame) {
  for (int y{0}; y < currentGame->getGridSize(); ++y) {
    for (int x{0}; x < currentGame->getGridSize(); ++x) {
      // Get the AABB for the object
      glm::vec3 boxMin =
          glm::vec3(x * plateau.tailleCase - (plateau.taille / 2.), 0,
                    y * plateau.tailleCase - (plateau.taille / 2.)); // AABB min
      glm::vec3 boxMax = glm::vec3(
          x * plateau.tailleCase - (plateau.taille / 2.) + plateau.tailleCase,
          0 + plateau.tailleCase * plateau.rapportHauteur,
          y * plateau.tailleCase - (plateau.taille / 2.) +
              plateau.tailleCase); // AABB max

      // Get tmin before intersection

      glm::vec3 rayOrigin = trackball.getPosition();
      if (rayIntersectsAABB(rayOrigin, mouse.ray, boxMin, boxMax,
                            mouse.collision.tHit)) {
        Piece *piece = currentGame->get_piece(x, y);

        if (piece && !currentGame->is_selected_piece() &&
            piece->get_color() == (currentGame->is_white_turn()
                                       ? PieceColor::WHITE
                                       : PieceColor::BLACK)) {
          currentGame->select_piece(piece);
        } else if (currentGame->is_selected_piece()) {
          currentGame->move_piece(x, y);
        }
      }
    }
  }
}