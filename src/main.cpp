#include <vector>
#include "MyLibs/OpenGLutils/object/object.hpp"
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
    App mainApp{};

    /* Initialize OpenGL */

    OpenGL_Manager* manager = mainApp.getManager();
    manager->OpenGL_init();

    /* Load the shader program */

    ShaderLoader shaderLoader;
    manager->setShaderLoader(&shaderLoader);
    glimac::FilePath applicationPath(argv[0]);
    manager->getShaderLoader()->loadShaders("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/src/shaders/triangle.vs.glsl", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/src/shaders/shader.fs.glsl");

    /* Her we have texture and objects loading */

    mainApp.getRender3D()->init_object();
    std::vector<Object>* obj_test = mainApp.getRender3D()->getObjectTest();
    mainApp.getRender3D()->init_mat_proj();

    /* ________________________________________________________________________ */

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    mainApp.set_chess_font(io.Fonts->AddFontFromFileTTF("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/font/CHEQ_TT.TTF", 30.f));

    mainApp.setup_app();

    ImFont* basicFont = io.Fonts->AddFontDefault();

    manager->ImGui_init();

    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose(manager->getWindow()))
    {
        /* Render here */
        mainApp.loop_opengl();

        mainApp.loop_imgui();

        /* Swap front and back buffers */
        glfwSwapBuffers(manager->getWindow());
        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}