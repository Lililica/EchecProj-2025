#include "renderOPENGL.hpp"

void RenderOpenGL::init_shaders() {

  // Load the shaders
  this->shaders = std::vector<ShaderLoader>(2);
  shaders[ShaderIndices::ShaderObj].loadShaders(SHADERS_PATH "triangle.vs.glsl",
                                                SHADERS_PATH "shader.fs.glsl");

  shaders[ShaderIndices::ShaderSkybox].loadShaders(
      SHADERS_PATH "skybox.vs.glsl", SHADERS_PATH "skybox.fs.glsl");

  // Set a defaukt shader to use
  manager.setShaderLoader(&shaders[ShaderIndices::ShaderObj]);
  manager.getShaderLoader()->useProgram();
}