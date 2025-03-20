#include "renderOPENGL.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

void RenderOpenGL::init_object()
{
    Object obj_test;
    obj_test.obj_loader("/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/texture/image.png", "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/obj/Car.obj");
    objects.push_back(obj_test);
}

void RenderOpenGL::draw_content()
{
    /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/
    trackball.rotateLeft(0.8);

    manager.update_window_size();
    manager.get_window_size(width, height);

    ProjMatrix   = glm::perspective(glm::radians(70.f), float(width) / height, 0.1f, 100.f);
    MVMatrix     = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -5.f));
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    MVP          = ProjMatrix * MVMatrix * trackball.getViewMatrix();

    glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uMVPMatrix"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uMVMatrix"), 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(glGetUniformLocation(manager.getShaderLoader()->getProgram()->getGLId(), "uNormalMatrix"), 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    glBindVertexArray(objects[0].getVAO()->getGLuint());
    glDrawArrays(GL_TRIANGLES, 0, objects[0].getVAO()->getSize());
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