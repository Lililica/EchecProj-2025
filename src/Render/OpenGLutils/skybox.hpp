#pragma once
#include <OpenGL/gltypes.h>
#include <vector>

class Skybox {

private:
  // Skybox vertices and indices
  GLuint skyboxVAO, skyboxVBO, skyboxEBO;
  GLuint cubemapTexture;

  std::vector<float> skyboxVertices = {
      //   Coordinates
      -1.0f, -1.0f, 1.0f,  //          7--------6
      1.0f,  -1.0f, 1.0f,  //         /|       /|
      1.0f,  -1.0f, -1.0f, //        4--------5 |
      -1.0f, -1.0f, -1.0f, //      | |      | |
      -1.0f, 1.0f,  1.0f,  //     | 3------|-2
      1.0f,  1.0f,  1.0f,  //     |/       |/
      1.0f,  1.0f,  -1.0f, //     0--------1
      -1.0f, 1.0f,  -1.0f};

  std::vector<unsigned int> skyboxIndices = {
      // Right
      1, 2, 6, 6, 5, 1,
      // Left
      0, 4, 7, 7, 3, 0,
      // Top
      4, 5, 6, 6, 7, 4,
      // Bottom
      0, 3, 2, 2, 1, 0,
      // Back
      0, 1, 5, 5, 4, 0,
      // Front
      3, 7, 6, 6, 2, 3};

  // Skybox texture
  std::vector<std::string> facesTextures = {
      ASSETS_PATH "texture/Skybox/Moonscape_E.jpg",
      ASSETS_PATH "texture/Skybox/Moonscape_W.jpg",
      ASSETS_PATH "texture/Skybox/Moonscape_U.jpg",
      ASSETS_PATH "texture/Skybox/Moonscape_D.jpg",
      ASSETS_PATH "texture/Skybox/Moonscape_N.jpg",
      ASSETS_PATH "texture/Skybox/Moonscape_S.jpg",
  };

public:
  Skybox() = default;
  ~Skybox() = default;

  void init_Vertex();
  void init_Texture();
  void draw(GLuint shaderProgram);
  void cleanup();

  GLuint getSkyboxVAO() const { return skyboxVAO; }
  GLuint getSkyboxVBO() const { return skyboxVBO; }
  GLuint getSkyboxEBO() const { return skyboxEBO; }
  GLuint getSkyboxTexture() const { return cubemapTexture; }
};