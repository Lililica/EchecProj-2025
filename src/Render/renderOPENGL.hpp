#pragma once

#include "MyLibs/OpenGLutils/object/object.hpp"
#include "MyLibs/OpenGLutils/utils.hpp"
#include "Render/TrackBall.hpp"

class RenderOpenGL {
private:
    OpenGL_Manager manager;

    std::vector<Object> objects;

    TrackballCamera trackball{0, 0, 0};

    int width  = 0;
    int height = 0;

    glm::mat4 ProjMatrix;
    glm::mat4 MVMatrix;
    glm::mat4 NormalMatrix;
    glm::mat4 MVP;

public:
    void draw_content();
    void init_object();

    Object*         getObjectTest() { return &objects[0]; }
    OpenGL_Manager* getManager() { return &manager; }
};