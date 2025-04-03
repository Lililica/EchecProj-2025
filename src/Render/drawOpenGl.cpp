#include "../Game/Piece/piece.hpp"
#include "../Game/game.hpp"
#include "mouseCasting.hpp"
#include "renderOPENGL.hpp"

void RenderOpenGL::drawCase(int& x, int& y, Game*& currentGame)
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
}

void RenderOpenGL::drawPiece(int& x, int& y, Piece*& piece)
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

void RenderOpenGL::selectCase(Game*& currentGame)
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
}

void RenderOpenGL::hoverCase(Game*& currentGame)
{
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
}