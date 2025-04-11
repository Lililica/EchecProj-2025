#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "renderOPENGL.hpp"
#include <optional>

void RenderOpenGL::draw_game(Game *&currentGame) {

  // Game section

  draw_board();

  for (std::optional<RandomMeteorite> &meteorite : meteorites) {
    draw_meteorites(meteorite);
  }

  for (int y{0}; y < currentGame->getGridSize(); ++y) {
    for (int x{0}; x < currentGame->getGridSize(); ++x) {
      draw_cases(currentGame, x, y);

      Piece *piece = currentGame->get_piece(x, y);
      if (piece) {
        draw_pieces(currentGame, x, y);
      }
    }
  }
}

void RenderOpenGL::draw_cases(Game *&currentGame, int x, int y) {

  MVMatrix = glm::translate(
      glm::mat4(1), glm::vec3(x * plateau.tailleCase - (plateau.taille / 2.), 0,
                              (y + 1) * plateau.tailleCase -
                                  (plateau.taille / 2.))); // Translation
  MVMatrix = glm::scale(MVMatrix,
                        glm::vec3(plateau.scaleCase,
                                  plateau.scaleCase * plateau.rapportHauteur,
                                  plateau.scaleCase)); // Translation * Rotation
                                                       // * Translation * Scale
  NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
  MVP = ProjMatrix * trackball.getViewMatrix() * MVMatrix;

  if (mouse.collision.xHit == x && mouse.collision.yHit == y)
    Color = glm::vec4(0.f, 1.f, 0.f, 1.f);
  else
    Color = (x + y) % 2 == 0 ? glm::vec4(0.1f, 0.1f, 0.1f, 1.f)
                             : glm::vec4(0.8f, 0.8f, 0.8f, 1.f);
  if (currentGame->is_selected_piece() &&
      currentGame->get_pos_selected_piece() == std::make_pair(x, y))
    Color = glm::vec4(0.f, 0.f, 1.f, 1.f);
  if (currentGame->is_selected_piece()) {
    auto possible_pos = currentGame->get_possible_pos();
    if (std::find(possible_pos.begin(), possible_pos.end(),
                  std::pair<int, int>{x, y}) != possible_pos.end()) {
      Color = glm::vec4(1.f, 0.f, 1.f, 1.f);
    }
    auto possible_attack = currentGame->get_attack_possible();
    if (std::find(possible_attack.begin(), possible_attack.end(),
                  std::pair<int, int>{x, y}) != possible_attack.end()) {
      Color = glm::vec4(1.f, 0.f, 0.f, 1.f);
    }
  }

  glUniformMatrix4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uMVPMatrix"),
      1, GL_FALSE, glm::value_ptr(MVP));
  glUniformMatrix4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uMVMatrix"),
      1, GL_FALSE, glm::value_ptr(MVMatrix));
  glUniformMatrix4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uNormalMatrix"),
      1, GL_FALSE, glm::value_ptr(NormalMatrix));
  glUniform4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uColor"),
      1, glm::value_ptr(Color));
  glUniform1i(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "isTexture"),
      0);

  glBindVertexArray(objects[ObjectType::Case].getVAO()->getGLuint());
  glDrawArrays(GL_TRIANGLES, 0, objects[ObjectType::Case].getVAO()->getSize());
  glBindVertexArray(0);
}

void RenderOpenGL::draw_pieces(Game *&currentGame, int x, int y) {
  // Piece section
  Piece *piece = currentGame->get_piece(x, y);
  int colorDirection = piece->get_color() == PieceColor::WHITE ? -1 : 1;
  PieceType type = piece->get_type();
  MVMatrix = glm::translate(
      glm::mat4(1),
      glm::vec3(x * plateau.tailleCase -
                    (plateau.taille - plateau.tailleCase) / 2.,
                0,
                y * plateau.tailleCase -
                    (plateau.taille - plateau.tailleCase) / 2.)); // Translation
  MVMatrix = glm::rotate(MVMatrix, -float(3.14 / 2),
                         glm::vec3(1, 0, 0)); // Translation * Rotation
  MVMatrix = glm::scale(
      MVMatrix,
      glm::vec3(plateau.scalePiece, plateau.scalePiece * colorDirection,
                plateau.scalePiece)); // Translation * Rotation *
                                      // Translation * Scale
  NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
  MVP = ProjMatrix * trackball.getViewMatrix() *
        MVMatrix; // Translation * Rotation * Translation

  Color = piece->get_color() == PieceColor::WHITE
              ? glm::vec4(1.f, 1.f, 1.f, 1.f)
              : glm::vec4(0.2f, 0.2f, 0.2f, 1.f);

  glUniformMatrix4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uMVPMatrix"),
      1, GL_FALSE, glm::value_ptr(MVP));
  glUniformMatrix4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uMVMatrix"),
      1, GL_FALSE, glm::value_ptr(MVMatrix));
  glUniformMatrix4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uNormalMatrix"),
      1, GL_FALSE, glm::value_ptr(NormalMatrix));
  glUniform4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uColor"),
      1, glm::value_ptr(Color));
  glUniform1i(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "isTexture"),
      0);
  glUniform3fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "viewPos"),
      1, glm::value_ptr(trackball.getPosition()));

  glBindVertexArray(objects[type].getVAO()->getGLuint());
  glBindTexture(GL_TEXTURE_2D,
                objects[ObjectType::Case].getTexture()->getTexture());
  glDrawArrays(GL_TRIANGLES, 0, objects[type].getVAO()->getSize());
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);
}

void RenderOpenGL::draw_board() {

  // Board section

  MVMatrix = glm::translate(
      glm::mat4(1), glm::vec3(-(plateau.taille / 2.) - 5,
                              plateau.rapportHauteur * plateau.scaleCase,
                              -(plateau.taille / 2.) - 5)); // Translation
  MVMatrix = glm::scale(
      MVMatrix, glm::vec3(80, 4 * plateau.rapportHauteur * plateau.scaleCase,
                          -80)); // Translation * Rotation
                                 // * Translation * Scale
  NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
  MVP = ProjMatrix * trackball.getViewMatrix() * MVMatrix;
  Color = glm::vec4(0.1f, 0.1f, 0.3f, 1.f);

  glUniformMatrix4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uMVPMatrix"),
      1, GL_FALSE, glm::value_ptr(MVP));
  glUniformMatrix4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uMVMatrix"),
      1, GL_FALSE, glm::value_ptr(MVMatrix));
  glUniformMatrix4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uNormalMatrix"),
      1, GL_FALSE, glm::value_ptr(NormalMatrix));
  glUniform4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uColor"),
      1, glm::value_ptr(Color));
  glUniform1i(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uTexture"),
      0);
  glUniform1i(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "isTexture"),
      1);

  glBindVertexArray(objects[ObjectType::Case].getVAO()->getGLuint());
  glBindTexture(GL_TEXTURE_2D,
                objects[ObjectType::Case].getTexture()->getTexture());
  glDrawArrays(GL_TRIANGLES, 0, objects[ObjectType::Case].getVAO()->getSize());
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);
}

void RenderOpenGL::draw_meteorites(std::optional<RandomMeteorite> &meteorite) {

  // Generate random meteorites
  if (!meteorite.has_value()) {
    meteorite = RandomMeteorite{};
    meteorite->up = randomDevice.randomIntUniforme(0, 1);
    meteorite->x = randomDevice.randomIntUniforme(-200, 200);
    meteorite->up ? meteorite->y = 200 : meteorite->y = -200;
    meteorite->z = randomDevice.randomIntUniforme(-200, 200);
    meteorite->scale = (randomDevice.randomDouble() * 10) + 5;
    meteorite->speed = randomDevice.randomDouble();

    meteorite->rotationX = randomDevice.randomDouble() * 2 * 3.14;
    meteorite->rotationSpeedX = randomDevice.randomDouble() * 0.05;

    meteorite->rotationY = randomDevice.randomDouble() * 2 * 3.14;
    meteorite->rotationSpeedY = randomDevice.randomDouble() * 0.05;

    meteorite->rotationZ = randomDevice.randomDouble() * 2 * 3.14;
    meteorite->rotationSpeedZ = randomDevice.randomDouble() * 0.05;
  }
  if (meteorite.has_value()) {
    meteorite->y -= meteorite->up ? meteorite->speed : -meteorite->speed;
    meteorite->rotationX += meteorite->rotationSpeedX;
    meteorite->rotationY += meteorite->rotationSpeedY;
    meteorite->rotationZ += meteorite->rotationSpeedZ;
  }
  if (meteorite->y < -200) {
    meteorite.reset();
  }

  MVMatrix =
      glm::translate(glm::mat4(1), glm::vec3(meteorite->x, meteorite->y,
                                             meteorite->z)); // Translation
  MVMatrix = glm::scale(MVMatrix, glm::vec3(meteorite->scale, meteorite->scale,
                                            meteorite->scale));
  MVMatrix = glm::rotate(MVMatrix, meteorite->rotationX,
                         glm::vec3(0, 1, 0)); // Rotation
  MVMatrix = glm::rotate(MVMatrix, meteorite->rotationY,
                         glm::vec3(1, 0, 0)); // Rotation
  MVMatrix = glm::rotate(MVMatrix, meteorite->rotationZ,
                         glm::vec3(0, 0, 1)); // Rotation
  NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
  MVP = ProjMatrix * trackball.getViewMatrix() * MVMatrix;

  glUniformMatrix4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uMVPMatrix"),
      1, GL_FALSE, glm::value_ptr(MVP));
  glUniformMatrix4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uMVMatrix"),
      1, GL_FALSE, glm::value_ptr(MVMatrix));
  glUniformMatrix4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uNormalMatrix"),
      1, GL_FALSE, glm::value_ptr(NormalMatrix));
  glUniform4fv(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uColor"),
      1, glm::value_ptr(Color));
  glUniform1i(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "uTexture"),
      0);
  glUniform1i(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "isTexture"),
      1);
  glUniform1i(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "isMeteor"),
      1);

  glBindVertexArray(objects[ObjectType::Meteorite].getVAO()->getGLuint());
  glBindTexture(GL_TEXTURE_2D,
                objects[ObjectType::Meteorite].getTexture()->getTexture());
  glDrawArrays(GL_TRIANGLES, 0,
               objects[ObjectType::Meteorite].getVAO()->getSize());
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);

  glUniform1i(
      glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(),
                           "isMeteor"),
      0);
}

void RenderOpenGL::draw_skybox() {
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
}