#pragma once

#include <vector>
#include "Game/Piece/cavalier.hpp"
#include "MyLibs/OpenGLutils/object/object.hpp"
#include "MyLibs/OpenGLutils/utils.hpp"
#include "Render/TrackBall.hpp"

class RenderOpenGL {
private:
    OpenGL_Manager manager;

    std::vector<Object> objects;

    int width  = WINDOW_WIDTH;
    int height = WINDOW_HEIGHT;

    glm::mat4 ProjMatrix;
    glm::mat4 MVMatrix;
    glm::mat4 NormalMatrix;
    glm::mat4 MVP;

    TrackballCamera trackball{0, 0, 0};

public:
    void draw_content();
    void button_action();

    void init_object();
    void init_mat_proj()
    {
        ProjMatrix   = glm::perspective(glm::radians(70.f), float(width) / height, 0.1f, 500.f);
        MVMatrix     = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -200.f));
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        MVP          = ProjMatrix * MVMatrix * trackball.getViewMatrix();
    }

    std::vector<Object>* getObjectTest() { return &objects; }
    OpenGL_Manager*      getManager() { return &manager; }
};