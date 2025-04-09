#pragma once

#include "Game/game.hpp"
#include "OpenGLutils/object/object.hpp"
#include "OpenGLutils/utils.hpp"
#include "Render/OpenGLutils/skybox.hpp"
#include "Render/TrackBall.hpp"
#include "Render/mouseCasting.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "shaders/ShaderReader.hpp"
#include <glm/glm.hpp>
#include <vector>

enum ObjectType { Case = 6 };

enum ShaderIndices {
  ShaderObj = 0,
  ShaderSkybox = 1,
};

struct GameDisplayInformation {
  float taille = 150.f;
  float rapportHauteur = -0.1f;
  float tailleCase = float(taille) / 8;

  float scaleCase = 9.f;
  float scalePiece = 0.3f;
};

class RenderOpenGL {
private:
  OpenGL_Manager manager;
  Skybox skybox;

  std::vector<Object> objects;
  std::vector<ShaderLoader> shaders;

  glm::mat4 ProjMatrix;
  glm::mat4 MVMatrix;
  glm::mat4 NormalMatrix;
  glm::mat4 MVP;
  glm::vec4 Color{1.f, 0.f, 0.f, 1.f};

  TrackballCamera trackball{200, 45., 90.};
  MouseInfo mouse;

  GameDisplayInformation plateau;

public:
  void init();
  void draw_content(Game *&currentGame);
  void button_action();
  void mouse_action(Game *&currentGame);

  // Drawing Game and Objects
  void draw_game(Game *&currentGame);

  void draw_cases(Game *&currentGame, int x, int y);
  void draw_pieces(Game *&currentGame, int x, int y);
  void draw_board();

  // Shader loading
  void init_shaders();

  // Object loading
  void init_object();

  // Projection matrix
  void reset_matrix() { init_mat_proj(); }
  void init_mat_proj() {
    ProjMatrix = glm::perspective(
        glm::radians(70.f), float(manager.getWidth()) / manager.getHeight(),
        0.1f, 2000.f);
    MVMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -500.f));
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    MVP = ProjMatrix * MVMatrix * trackball.getViewMatrix();
  }

  OpenGL_Manager *getManager() { return &manager; }
};