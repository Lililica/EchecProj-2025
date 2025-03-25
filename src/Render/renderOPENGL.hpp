#pragma once

#include <vector>
#include "Game/Piece/cavalier.hpp"
#include "MyLibs/OpenGLutils/object/object.hpp"
#include "MyLibs/OpenGLutils/utils.hpp"
#include "Render/TrackBall.hpp"

struct GameDisplayInformation {
    float taille     = 150.f;
    float tailleCase = float(taille) / 8;

    float scaleCase  = 9.f;
    float scalePiece = 0.3f;
};

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

    TrackballCamera trackball{200, 45., 90.};

    GameDisplayInformation plateau;

public:
    void draw_content(Game*& currentGame);
    void button_action();
    void draw_game(Game*& currentGame);
    void reset_matrix()
    {
        init_mat_proj();
    }

    void init_object();
    void init_mat_proj()
    {
        ProjMatrix   = glm::perspective(glm::radians(70.f), float(width) / height, 0.1f, 500.f);
        MVMatrix     = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -500.f));
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        MVP          = ProjMatrix * MVMatrix * trackball.getViewMatrix();
    }

    std::vector<Object>* getObjectTest() { return &objects; }
    OpenGL_Manager*      getManager() { return &manager; }
};