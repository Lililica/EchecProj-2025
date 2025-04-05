#pragma once

#include <vector>
#include "Game/Piece/cavalier.hpp"
#include "Game/game.hpp"
#include "MyLibs/OpenGLutils/object/object.hpp"
#include "MyLibs/OpenGLutils/utils.hpp"
#include "TrackBall.hpp"
#include "glm/ext/vector_float3.hpp"

enum ObjectType { Case = 10 };

struct GameDisplayInformation {
    float taille         = 150.f;
    float rapportHauteur = -0.1f;
    float tailleCase     = float(taille) / 8;

    float scaleCase  = 9.f;
    float scalePiece = 0.3f;
};

struct tCollision {
    float tHit = 10000000;
    int   xHit = -1;
    int   yHit = -1;
};

struct MouseInfo {
    bool       isPressed;
    int        x;
    int        y;
    glm::vec3  ray;
    tCollision collision;
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
    glm::vec4 Color{1.f, 0.f, 0.f, 1.f};

    TrackballCamera trackball{200, 45., 90.};
    MouseInfo       mouse;

    GameDisplayInformation plateau;

public:
    void draw_content(Game*& currentGame);
    void button_action();
    void mouse_action(Game*& currentGame);
    void draw_game(Game*& currentGame);
    void reset_matrix()
    {
        init_mat_proj();
    }

    void init_object();
    void init_mat_proj()
    {
        ProjMatrix   = glm::perspective(glm::radians(70.f), float(width) / height, 0.1f, 300.f);
        MVMatrix     = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -500.f));
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        MVP          = ProjMatrix * MVMatrix * trackball.getViewMatrix();
    }

    std::vector<Object>* getObjectTest() { return &objects; }
    OpenGL_Manager*      getManager() { return &manager; }

    void drawCase(int& x, int& y, Game*& currentGame);
    void drawPiece(int& x, int& y, Piece*& piece);
    void selectCase(Game*& currentGame);
    void hoverCase(Game*& currentGame);
};