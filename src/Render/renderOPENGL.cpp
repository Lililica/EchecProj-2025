#include "renderOPENGL.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"

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
  manager.setShaderLoader(&shaders[ShaderIndices::ShaderSkybox]);
  manager.getShaderLoader()->useProgram();

  glDepthFunc(GL_LEQUAL);
  glDepthMask(GL_FALSE);

  glm::mat4 view = glm::mat4(
      glm::mat3(glm::lookAt(glm::normalize(trackball.getPosition()),
                            glm::vec3(0., 0., 0.), glm::vec3(0, 1, 0))));

  glUniform1i(glGetUniformLocation(
                  manager.getShaderLoader()->getProgram()->getGLId(), "skybox"),
              0);
  glUniformMatrix4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "view"),
      1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "projection"),
      1, GL_FALSE, glm::value_ptr(ProjMatrix));

  glBindVertexArray(skybox.getSkyboxVAO());
  glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.getSkyboxTexture());
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  glBindVertexArray(0);

  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LESS);

  /* ------------------------ */

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

      // Get tmin before intersection

      glm::vec3 rayOrigin = trackball.getPosition();
      if (rayIntersectsAABB(rayOrigin, mouse.ray, boxMin, boxMax,
                            mouse.collision.tHit)) {
        mouse.collision.xHit = x;
        mouse.collision.yHit = y;
        // std::cout << "Intersection detected at t = " << mouse.collision.tHit
        // << " at case numbre " << y + x * currentGame->getGridSize() <<
        // std::endl;
      }
    }
  }

  if (glfwGetMouseButton(manager.getWindow(), GLFW_MOUSE_BUTTON_LEFT) ==
      GLFW_PRESS) {
    if (!mouse.isPressed) {
      // Select a case
      for (int y{0}; y < currentGame->getGridSize(); ++y) {
        for (int x{0}; x < currentGame->getGridSize(); ++x) {
          // Get the AABB for the object
          glm::vec3 boxMin = glm::vec3(
              x * plateau.tailleCase - (plateau.taille / 2.), 0,
              y * plateau.tailleCase - (plateau.taille / 2.)); // AABB min
          glm::vec3 boxMax =
              glm::vec3(x * plateau.tailleCase - (plateau.taille / 2.) +
                            plateau.tailleCase,
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

      if (!mouse.isPressed)
        mouse.isPressed = true;
    }
  } else {
    if (mouse.isPressed)
      mouse.isPressed = false;
  }
}