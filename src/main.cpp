#include "Render/OpenGLutils/object/object.hpp"
#include "Render/OpenGLutils/utils.hpp"
#define GL_SILENCE_DEPRECATION
#include "app.hpp"
#include <OpenGL/gl.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <cstddef>
#include <imgui.h>
#include <quick_imgui/quick_imgui.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(int argc, char **argv) {
  App mainApp{};

  // Render 3D init
  mainApp.getRender3D()->init();

  /* ________________________________________________________________________ */
  // /* ImGui init */

  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();

  mainApp.init_font(
      io.Fonts->AddFontFromFileTTF(ASSETS_PATH "font/CHEQ_TT.TTF", 30.f));

  mainApp.setup_app();

  mainApp.getManager()->ImGui_init();

  /* Loop until the user closes the window */

  while (!glfwWindowShouldClose(mainApp.getManager()->getWindow())) {
    /* Render here */
    mainApp.loop_opengl();

    mainApp.loop_imgui();

    /* Swap front and back buffers */
    glfwSwapBuffers(mainApp.getManager()->getWindow());
    /* Poll for and process events */
    glfwPollEvents();
  }

  ImGui_ImplGlfw_Shutdown();
  ImGui_ImplOpenGL3_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
  return 0;
}