#pragma once

#include <glad/glad.h>
#include <glfw/src/internal.h>
#include "../../shaders/ShaderReader.hpp"
#include "GLFW/glfw3.h"
#include "callback.hpp"

class OpenGL_Manager {
private:
    GLFWwindow* window;

    ShaderLoader* shaderLoader;

    int width  = WINDOW_WIDTH;
    int height = WINDOW_HEIGHT;

public:
    GLFWwindow*   getWindow() { return window; }
    ShaderLoader* getShaderLoader() { return shaderLoader; }

    void setWindow(GLFWwindow* w) { window = w; }

    void setShaderLoader(ShaderLoader* s) { shaderLoader = s; }

    void update_window_size()
    {
        glfwGetWindowSize(window, &width, &height);
    }
    void get_window_size(int& w, int& h)
    {
        w = width;
        h = height;
    }

    void OpenGL_init();
    void ImGui_init();

    /* ________________________________________ */

    /* ________________________________________ */
};
