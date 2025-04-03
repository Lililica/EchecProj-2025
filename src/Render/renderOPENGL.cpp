#include "renderOPENGL.hpp"
#include <glfw/src/internal.h>
#include <iostream>
#include "MyLibs/OpenGLutils/object/texture.hpp"
#include "Render/mouseCasting.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <math.h>
#include <glm/glm.hpp>
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
    mouse.collision.tHit = 10000000;
    for (int y{0}; y < currentGame->getGridSize(); ++y)
    {
        for (int x{0}; x < currentGame->getGridSize(); ++x)
        {
            // Get the AABB for the object
            glm::vec3 boxMin = glm::vec3(x * plateau.tailleCase - (plateau.taille / 2.), 0, y * plateau.tailleCase - (plateau.taille / 2.));                                                                                         // AABB min
            glm::vec3 boxMax = glm::vec3(x * plateau.tailleCase - (plateau.taille / 2.) + plateau.tailleCase, 0 + plateau.tailleCase * plateau.rapportHauteur, y * plateau.tailleCase - (plateau.taille / 2.) + plateau.tailleCase); // AABB max

            // Get tmin before intersection

            glm::vec3 rayOrigin = trackball.getPosition();
            if (rayIntersectsAABB(rayOrigin, mouse.ray, boxMin, boxMax, mouse.collision.tHit))
            {
                mouse.collision.xHit = x;
                mouse.collision.yHit = y;
                // std::cout << "Intersection detected at t = " << mouse.collision.tHit << " at case numbre " << y + x * currentGame->getGridSize() << std::endl;
            }
        }
    }

    if (glfwGetMouseButton(manager.getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        if (!mouse.isPressed)
        {
            for (int y{0}; y < currentGame->getGridSize(); ++y)
            {
                for (int x{0}; x < currentGame->getGridSize(); ++x)
                {
                    // Get the AABB for the object
                    glm::vec3 boxMin = glm::vec3(x * plateau.tailleCase - (plateau.taille / 2.), 0, y * plateau.tailleCase - (plateau.taille / 2.));                                                                                         // AABB min
                    glm::vec3 boxMax = glm::vec3(x * plateau.tailleCase - (plateau.taille / 2.) + plateau.tailleCase, 0 + plateau.tailleCase * plateau.rapportHauteur, y * plateau.tailleCase - (plateau.taille / 2.) + plateau.tailleCase); // AABB max

                    // Get tmin before intersection

                    glm::vec3 rayOrigin = trackball.getPosition();
                    if (rayIntersectsAABB(rayOrigin, mouse.ray, boxMin, boxMax, mouse.collision.tHit))
                    {
                        Piece* piece = currentGame->get_piece(x, y);

                        if (piece && !currentGame->is_selected_piece() && piece->get_color() == (currentGame->is_white_turn() ? PieceColor::WHITE : PieceColor::BLACK))
                        {
                            currentGame->select_piece(piece);
                        }
                        else if (currentGame->is_selected_piece())
                        {
                            currentGame->move_piece(x, y);
                        }
                    }
                }
            }

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
    glClearColor(1.f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int y{0}; y < currentGame->getGridSize(); ++y)
    {
        for (int x{0}; x < currentGame->getGridSize(); ++x)
        {
            MVMatrix     = glm::translate(glm::mat4(1), glm::vec3(x * plateau.tailleCase - (plateau.taille / 2.), 0, (y + 1) * plateau.tailleCase - (plateau.taille / 2.))); // Translation
            MVMatrix     = glm::scale(MVMatrix, glm::vec3(plateau.scaleCase, plateau.scaleCase * plateau.rapportHauteur, plateau.scaleCase));                                // Translation * Rotation * Translation * Scale
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            MVP          = ProjMatrix * trackball.getViewMatrix() * MVMatrix;
            if (mouse.collision.xHit == x && mouse.collision.yHit == y)
                Color = glm::vec4(0.f, 1.f, 0.f, 1.f);
            else
                Color = glm::vec4(0.5f, 0.5f, 0.5f, 1.f);
            if (currentGame->is_selected_piece() && currentGame->get_pos_selected_piece() == std::make_pair(x, y))
                Color = glm::vec4(0.f, 0.f, 1.f, 1.f);
            if (currentGame->is_selected_piece())
            {
                auto possible_pos = currentGame->get_possible_pos();
                if (std::find(possible_pos.begin(), possible_pos.end(), std::pair<int, int>{x, y}) != possible_pos.end())
                {
                    Color = glm::vec4(1.f, 0.f, 1.f, 1.f);
                }
                auto possible_attack = currentGame->get_attack_possible();
                if (std::find(possible_attack.begin(), possible_attack.end(), std::pair<int, int>{x, y}) != possible_attack.end())
                {
                    Color = glm::vec4(1.f, 0.f, 0.f, 1.f);
                }
            }

            glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uMVPMatrix"), 1, GL_FALSE, glm::value_ptr(MVP));
            glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uMVMatrix"), 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uNormalMatrix"), 1, GL_FALSE, glm::value_ptr(NormalMatrix));
            glUniform4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uColor"), 1, glm::value_ptr(Color));

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

                Color = piece->get_color() == PieceColor::WHITE ? glm::vec4(1.f, 1.f, 1.f, 1.f) : glm::vec4(0.f, 0.f, 0.f, 1.f);

                glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uMVPMatrix"), 1, GL_FALSE, glm::value_ptr(MVP));
                glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uMVMatrix"), 1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uNormalMatrix"), 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                glUniform4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uColor"), 1, glm::value_ptr(Color));

                glBindVertexArray(objects[type].getVAO()->getGLuint());
                glDrawArrays(GL_TRIANGLES, 0, objects[type].getVAO()->getSize());
                glBindVertexArray(0);
            }
        }
    }
}