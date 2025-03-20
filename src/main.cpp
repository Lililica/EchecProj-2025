#include "MyLibs/OpenGLutils/utils.hpp"
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <cstddef>
#include <quick_imgui/quick_imgui.hpp>
#include "MyLibs/glimac/FilePath.hpp"
#include "app.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Render/TrackBall.hpp"

int main(int argc, char** argv)
{
    /* Initialize OpenGL */

    OpenGL_Manager manager;
    manager.OpenGL_init();

    /* Load the shader program */

    ShaderLoader shaderLoader;
    manager.setShaderLoader(&shaderLoader);
    glimac::FilePath applicationPath(argv[0]);
    manager.getShaderLoader()->loadShaders("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/src/shaders/triangle.vs.glsl", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/src/shaders/shader.fs.glsl");

    /* Her we have texture and objects loading */

    Object obj_test;
    obj_test.obj_loader("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/texture/image.png", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/obj/Car.obj");

    /* ________________________________________________________________________ */

    App mainApp{};

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    mainApp.set_chess_font(io.Fonts->AddFontFromFileTTF("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/font/CHEQ_TT.TTF", 50.f));

    mainApp.setup_app();

    ImFont* basicFont = io.Fonts->AddFontDefault();

    manager.ImGui_init();

    /* Loop until the user closes the window */

    TrackballCamera trackball{0, 0, 0};

    int width  = 0;
    int height = 0;

    glm::mat4 ProjMatrix;
    glm::mat4 MVMatrix;
    glm::mat4 NormalMatrix;
    glm::mat4 MVP;

    while (!glfwWindowShouldClose(manager.getWindow()))
    {
        glClearColor(1.f, 0.5f, 0.5f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        trackball.rotateLeft(0.8);

        manager.update_window_size();
        manager.get_window_size(width, height);

        ProjMatrix   = glm::perspective(glm::radians(70.f), float(width) / height, 0.1f, 100.f);
        MVMatrix     = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -5.f));
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        MVP          = ProjMatrix * MVMatrix * trackball.getViewMatrix();

        glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uMVPMatrix"), 1, GL_FALSE, glm::value_ptr(MVP));
        glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uMVMatrix"), 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uNormalMatrix"), 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        glBindVertexArray(obj_test.getVAO()->getGLuint());
        glDrawArrays(GL_TRIANGLES, 0, obj_test.getVAO()->getSize());
        glBindVertexArray(0);

        /*
          MVMatrix     = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));               // Translation
          MVMatrix     = glm::rotate(MVMatrix, float(glfwGetTime()), glm::vec3(0, 1, 0)); // Translation * Rotation
          MVMatrix     = glm::translate(MVMatrix, glm::vec3(-2, 0, 0));                   // Translation * Rotation * Translation
          MVMatrix     = glm::scale(MVMatrix, glm::vec3(0.2, 0.2, 0.2));                  // Translation * Rotation * Translation * Scale
          ProjMatrix   = glm::perspective(glm::radians(70.f), float(width) / height, 0.1f, 100.f);
          NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
          MVP          = ProjMatrix * MVMatrix * trackball.getViewMatrix(); // Translation * Rotation * Translation

          glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVPMatrix"), 1, GL_FALSE, glm::value_ptr(MVP));
          glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVMatrix"), 1, GL_FALSE, glm::value_ptr(MVMatrix));
          glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uNormalMatrix"), 1, GL_FALSE, glm::value_ptr(NormalMatrix));

          glBindVertexArray(VAO);
          glBindTexture(GL_TEXTURE_2D, texture);
          glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
          glBindTexture(GL_TEXTURE_2D, 0);
          glBindVertexArray(0);
        */

        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        ImGui::PushFont(basicFont);
        ImGui::Begin("Echec Game");

        mainApp.update_app();

        ImGui::PopFont();

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(manager.getWindow());
        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}