#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <cstddef>
#include <iostream>
#include <quick_imgui/quick_imgui.hpp>
#include "MyLibs/glimac/FilePath.hpp"
#include "MyLibs/glimac/Program.hpp"
#include "MyLibs/glimac/Sphere.hpp"
#include "MyLibs/glimac/common.hpp"
#include "app.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "MyLibs/ObjLoader/objloader.hpp"
#include "shaders/ShaderReader.hpp"

// int main()
// {
//     App mainApp{};

//     ImGui::CreateContext();
//     ImGuiIO& io = ImGui::GetIO();

//     mainApp.set_chess_font(io.Fonts->AddFontFromFileTTF("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/CHEQ_TT.TTF", 50.f));

//     mainApp.setup_app();

//     ImFont* basicFont = io.Fonts->AddFontDefault();

//     quick_imgui::loop(
//         "Chess",
//         /* init: */ [&]() {},
//         /* loop: */
//         [&]() {
//             ImGui::PushFont(basicFont);
//             ImGui::ShowDemoWindow(); // This opens a window which shows tons of examples of what you can do with ImGui. You should check it out! Also, you can use the "Item Picker" in the top menu of that demo window: then click on any widget and it will show you the corresponding code directly in your IDE!

//             ImGui::Begin("Echec Game");

//             mainApp.update_app();

//             ImGui::PopFont();

//             ImGui::End();
//         }
//     );
// }

int const window_width  = 800;
int const window_height = 800;

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
    width  = window_width;
    height = window_height;
}

struct Vertex2DColor {
    glm::vec2 position;
    glm::vec3 color;

    Vertex2DColor();
    Vertex2DColor(const glm::vec2 p, const glm::vec3 c)
        : position(p), color(c) {};
};

int main(int argc, char** argv)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

/* Create a window and its OpenGL context */
#ifdef __APPLE__
    /* We need to explicitly ask for a 3.3 context on Mac */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    GLFWwindow* window =
        glfwCreateWindow(window_width, window_height, "TP1", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Intialize glad (loads the OpenGL functions) */
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        return -1;
    }

    /* Hook input callbacks */
    glfwSetKeyCallback(window, &key_callback);
    glfwSetMouseButtonCallback(window, &mouse_button_callback);
    glfwSetScrollCallback(window, &scroll_callback);
    glfwSetCursorPosCallback(window, &cursor_position_callback);
    glfwSetWindowSizeCallback(window, &size_callback);

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    /* ________________________________________________________________________ */

    /* Load the shader program */

    glimac::FilePath applicationPath(argv[0]);
    glimac::Program  program =
        glimac::loadProgram("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/src/shaders/triangle.vs.glsl", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/src/shaders/shader.fs.glsl");
    program.use();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH);

    // std::string pathTest = "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/Car.obj";
    // objLoader.add_path(pathTest);
    // std::vector<GLfloat> vertices = objLoader.loaderObj();

    glimac::Sphere sphere(1, 32, 16);

    GLuint VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glimac::ShapeVertex) * sphere.getVertexCount(), sphere.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), 1.f, 0.1f, 100.f);
    glm::mat4 MVMatrix     = glm::translate(ProjMatrix, glm::vec3(0.f, 0.f, -5.f));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    glm::mat4 MVP          = ProjMatrix * MVMatrix;

    /* ________________________________________________________________________ */

    // App mainApp{};

    // ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO();

    // mainApp.set_chess_font(io.Fonts->AddFontFromFileTTF("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/CHEQ_TT.TTF", 50.f));

    // mainApp.setup_app();

    // ImFont* basicFont = io.Fonts->AddFontDefault();

    // ImGui_ImplGlfw_InitForOpenGL(window, true);
    // ImGui_ImplOpenGL3_Init("#version 330");

    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.f, 0.5f, 0.5f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVPMatrix"), 1, GL_FALSE, glm::value_ptr(MVP));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVMatrix"), 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uNormalMatrix"), 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
        glBindVertexArray(0);

        // ImGui_ImplGlfw_NewFrame();
        // ImGui_ImplOpenGL3_NewFrame();
        // ImGui::NewFrame();

        // ImGui::PushFont(basicFont);
        // ImGui::Begin("Echec Game");

        // mainApp.update_app();

        // ImGui::PopFont();

        // ImGui::End();

        // ImGui::Render();
        // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    // ImGui_ImplGlfw_Shutdown();
    // ImGui_ImplOpenGL3_Shutdown();
    // ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}