#include "renderOPENGL.hpp"
#include "Game/Piece/cavalier.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../Game/Piece/piece.hpp"

void RenderOpenGL::init_object()
{
    this->objects = std::vector<Object>(6);
    objects[PieceType::PION].obj_loader("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/texture/image.png", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/obj/Pawn.obj");
    objects[PieceType::TOUR].obj_loader("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/texture/image.png", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/obj/Rook.obj");
    objects[PieceType::ROI].obj_loader("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/texture/image.png", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/obj/King.obj");
    objects[PieceType::DAME].obj_loader("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/texture/image.png", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/obj/Queen.obj");
    objects[PieceType::FOU].obj_loader("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/texture/image.png", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/obj/Bishop.obj");
    objects[PieceType::CAVALIER].obj_loader("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/texture/image.png", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/obj/Knight.obj");
}

void RenderOpenGL::draw_content()
{
    /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/

    manager.update_window_size();

    button_action();

    glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uMVPMatrix"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uMVMatrix"), 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uNormalMatrix"), 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    glBindVertexArray(objects[PieceType::CAVALIER].getVAO()->getGLuint());
    glDrawArrays(GL_TRIANGLES, 0, objects[PieceType::CAVALIER].getVAO()->getSize());
    glBindVertexArray(0);

    /*
      MVMatrix     = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));               // Translation
      MVMatrix     = glm::rotate(MVMatrix, float(glfwGetTime()), glm::vec3(0, 1, 0)); // Translation * Rotation
      MVMatrix     = glm::translate(MVMatrix, glm::vec3(-2, 0, 0));                   // Translation * Rotation * Translation
      MVMatrix     = glm::scale(MVMatrix, glm::vec3(0.2, 0.2, 0.2));                  // Translation * Rotation * Translation * Scale
      ProjMatrix   = glm::perspective(glm::radians(70.f), float(width) / height, 0.1f, 100.f);
      NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
      MVP          = ProjMatrix * MVMatrix * trackball.getViewMatrix(); // Translation * Rotation * Translation

      glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVPMatrix"), 1, GL_FALSE, glm::value_ptr(MVP));
      glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVMatrix"), 1, GL_FALSE, glm::value_ptr(MVMatrix));
      glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uNormalMatrix"), 1, GL_FALSE, glm::value_ptr(NormalMatrix));

      glBindVertexArray(VAO);
      glBindTexture(GL_TEXTURE_2D, texture);
      glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
      glBindTexture(GL_TEXTURE_2D, 0);
      glBindVertexArray(0);
    */
}

void RenderOpenGL::button_action()
{
    if (glfwGetKey(manager.getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        trackball.rotateLeft(0.8);
        MVP = ProjMatrix * MVMatrix * trackball.getViewMatrix();
    }
    if (glfwGetKey(manager.getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        trackball.rotateLeft(-0.8);
        MVP = ProjMatrix * MVMatrix * trackball.getViewMatrix();
    }
    if (glfwGetKey(manager.getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
    {
        trackball.rotateUp(0.8);
        MVP = ProjMatrix * MVMatrix * trackball.getViewMatrix();
    }
    if (glfwGetKey(manager.getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        trackball.rotateUp(-0.8);
        MVP = ProjMatrix * MVMatrix * trackball.getViewMatrix();
    }
}