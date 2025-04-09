#pragma once

#include "Render/OpenGLutils/ObjLoader/objloader.hpp"
#include <cstddef>
#include <glad/glad.h>
#include <iostream>
#include <string>

class VAO {
private:
  GLuint vao{};
  size_t size;
  GLuint vbo{};

public:
  VAO() = default;

  ~VAO() {
    glDeleteVertexArrays(1, &vao);
    std::cout << "VAO deleted" << '\n';
  };

  void init_vao(const std::string &path) {
    ObjLoader objLoader(path);
    std::vector<Vertex> vertices = objLoader.loaderObj();

    vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
                 vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->size = vertices.size();
  }

  GLuint getGLuint() const { return vao; }
  size_t getSize() const { return size; }
};
