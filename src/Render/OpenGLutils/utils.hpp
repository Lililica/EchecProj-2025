#pragma once

#include "../../shaders/ShaderReader.hpp"
#include "GLFW/glfw3.h"

#include <glad/glad.h>

class OpenGL_Manager {
private:
  GLFWwindow *window;
  ShaderLoader *shaderLoader;
  int width = 800;
  int height = 800;

public:
  GLFWwindow *getWindow() { return window; }
  ShaderLoader *getShaderLoader() { return shaderLoader; }

  void setWindow(GLFWwindow *w) { window = w; }
  void setShaderLoader(ShaderLoader *s) { shaderLoader = s; }

  void update_window_size() { glfwGetWindowSize(window, &width, &height); }

  int getWidth() { return width; }
  int getHeight() { return height; }

  void OpenGL_init();
  void ImGui_init();

  /* ________________________________________ */

  /* ________________________________________ */
};
