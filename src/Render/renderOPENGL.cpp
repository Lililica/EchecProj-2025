#include "renderOPENGL.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glfw/src/internal.h>
#include <glm/glm.hpp>
#include "../Game/Piece/piece.hpp"
#include "../Game/game.hpp"
#include "mouseCasting.hpp"

void RenderOpenGL::init_object()
{
    this->objects = std::vector<Object>(7);
    objects[PieceType::PION].obj_loader("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/texture/image.png", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/obj/Pawn.obj");
    objects[PieceType::TOUR].obj_loader("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/texture/image.png", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/obj/Rook.obj");
    objects[PieceType::ROI].obj_loader("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/texture/image.png", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/obj/King.obj");
    objects[PieceType::DAME].obj_loader("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/texture/image.png", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/obj/Queen.obj");
    objects[PieceType::FOU].obj_loader("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/texture/image.png", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/obj/Bishop.obj");
    objects[PieceType::CAVALIER].obj_loader("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/texture/image.png", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/obj/Knight.obj");
    objects[ObjectType::Case].obj_loader("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/texture/image.png", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/obj/case.obj");
}

void RenderOpenGL::draw_content(Game*& currentGame)
{
    manager.get_window_size(width, height);

    ProjMatrix = glm::perspective(glm::radians(70.f), float(width) / height, 0.1f, 500.f);

    button_action();
    mouse_action(currentGame);

    draw_game(currentGame);
}

void RenderOpenGL::button_action()
{
    if (glfwGetKey(manager.getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
        trackball.rotateLeft(0.8);

    if (glfwGetKey(manager.getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
        trackball.rotateLeft(-0.8);

    if (glfwGetKey(manager.getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
        trackball.rotateUp(-0.8);

    if (glfwGetKey(manager.getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
        trackball.rotateUp(0.8);

    if (glfwGetKey(manager.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        trackball.moveFront(-0.3);

    if (glfwGetKey(manager.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        trackball.moveFront(0.3);
}

void RenderOpenGL::mouse_action(Game*& currentGame)
{
    double xpos = 0;
    double ypos = 0;
    glfwGetCursorPos(manager.getWindow(), &xpos, &ypos);
    mouse.x = static_cast<int>(xpos);
    mouse.y = static_cast<int>(ypos);

    // Get the ray from the mouse position
    mouse.ray = getRayFromMouse(mouse.x, mouse.y, width, height, trackball.getViewMatrix(), ProjMatrix);

    // Hover over the object
    hoverCase(currentGame);

    if (glfwGetMouseButton(manager.getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        if (!mouse.isPressed)
        {
            // Select a case
            selectCase(currentGame);

            if (!mouse.isPressed)
                mouse.isPressed = true;
        }
    }
    else
    {
        if (mouse.isPressed)
            mouse.isPressed = false;
    }
}

void RenderOpenGL::draw_game(Game*& currentGame)
{
    for (int y{0}; y < currentGame->getGridSize(); ++y)
    {
        for (int x{0}; x < currentGame->getGridSize(); ++x)
        {
            drawCase(x, y, currentGame);

            Piece* piece = currentGame->get_piece(x, y);
            if (piece)
            {
                drawPiece(x, y, piece);
            }
        }
    }
}