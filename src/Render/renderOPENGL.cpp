#include "renderOPENGL.hpp"
#include "Game/Piece/cavalier.hpp"
#include "MyLibs/OpenGLutils/ObjLoader/objloader.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <numbers>
#include "../Game/Piece/piece.hpp"
#include "../Game/game.hpp"

enum ObjectType { Case = 6 };

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
    /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/

    manager.update_window_size();
    manager.get_window_size(width, height);
    ProjMatrix = glm::perspective(glm::radians(70.f), float(width) / height, 0.1f, 500.f);

    button_action();

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

void RenderOpenGL::draw_game(Game*& currentGame)
{
    for (int y{0}; y < currentGame->getGridSize(); ++y)
    {
        for (int x{0}; x < currentGame->getGridSize(); ++x)
        {
            MVMatrix     = glm::translate(glm::mat4(1), glm::vec3(x * plateau.tailleCase - (plateau.taille - plateau.tailleCase) / 2., 0, y * plateau.tailleCase - (plateau.taille - plateau.tailleCase) / 2.)); // Translation
            MVMatrix     = glm::scale(MVMatrix, glm::vec3(plateau.scaleCase, plateau.scaleCase, plateau.scaleCase));                                                                                             // Translation * Rotation * Translation * Scale
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            MVP          = ProjMatrix * trackball.getViewMatrix() * MVMatrix;

            glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uMVPMatrix"), 1, GL_FALSE, glm::value_ptr(MVP));
            glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uMVMatrix"), 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uNormalMatrix"), 1, GL_FALSE, glm::value_ptr(NormalMatrix));

            glBindVertexArray(objects[ObjectType::Case].getVAO()->getGLuint());
            glDrawArrays(GL_TRIANGLES, 0, objects[ObjectType::Case].getVAO()->getSize());
            glBindVertexArray(0);

            Piece* piece = currentGame->get_piece(x, y);
            if (piece)
            {
                int       colorDirection = piece->get_color() == PieceColor::WHITE ? -1 : 1;
                PieceType type           = piece->get_type();
                MVMatrix                 = glm::translate(glm::mat4(1), glm::vec3(x * plateau.tailleCase - (plateau.taille - plateau.tailleCase) / 2., 0, y * plateau.tailleCase - (plateau.taille - plateau.tailleCase) / 2.)); // Translation
                MVMatrix                 = glm::rotate(MVMatrix, -float(3.14 / 2), glm::vec3(1, 0, 0));                                                                                                                          // Translation * Rotation
                MVMatrix                 = glm::scale(MVMatrix, glm::vec3(plateau.scalePiece, plateau.scalePiece * colorDirection, plateau.scalePiece));                                                                         // Translation * Rotation * Translation * Scale
                NormalMatrix             = glm::transpose(glm::inverse(MVMatrix));
                MVP                      = ProjMatrix * trackball.getViewMatrix() * MVMatrix; // Translation * Rotation * Translation

                glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uMVPMatrix"), 1, GL_FALSE, glm::value_ptr(MVP));
                glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uMVMatrix"), 1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uNormalMatrix"), 1, GL_FALSE, glm::value_ptr(NormalMatrix));

                glBindVertexArray(objects[type].getVAO()->getGLuint());
                glDrawArrays(GL_TRIANGLES, 0, objects[type].getVAO()->getSize());
                glBindVertexArray(0);
            }
        }
    }
}