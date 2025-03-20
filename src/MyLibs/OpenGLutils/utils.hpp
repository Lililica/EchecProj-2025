#pragma once

#include <glad/glad.h>
#include <glfw/src/internal.h>
#include "../../shaders/ShaderReader.hpp"

static int const WINDOW_WIDTH  = 800;
static int const WINDOW_HEIGHT = 800;

class OpenGL_Manager {
private:
    GLFWwindow*   window;
    ShaderLoader* shaderLoader;
    int           width  = 0;
    int           height = 0;

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

    static void key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
    {
        if (key == GLFW_KEY_A && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    static void mouse_button_callback(GLFWwindow* /*window*/, int /*button*/, int /*action*/, int /*mods*/) {}

    static void scroll_callback(GLFWwindow* /*window*/, double /*xoffset*/, double /*yoffset*/) {}

    static void cursor_position_callback(GLFWwindow* /*window*/, double /*xpos*/, double /*ypos*/) {}

    static void size_callback(GLFWwindow* /*window*/, int width, int height)
    {
        width  = WINDOW_WIDTH;
        height = WINDOW_HEIGHT;
    }
};
