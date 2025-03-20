#pragma once

#include <glad/glad.h>
#include <glfw/src/internal.h>
#include <cstddef>
#include <string>
#include <vector>
#include "MyLibs/OpenGLutils/ObjLoader/objloader.hpp"
#include "MyLibs/glimac/common.hpp"

class VAO {
private:
    GLuint vao{};
    size_t size;

public:
    VAO() = default;
    VAO(const std::string& path)
    {
        ObjLoader           objLoader(path);
        std::vector<Vertex> vertices = objLoader.loaderObj();

        GLuint VBO = 0;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenVertexArrays(1, &this->vao);
        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        this->size = vertices.size();
    };
    ~VAO()
    {
        glDeleteVertexArrays(1, &vao);
    };

    GLuint getGLuint() const { return vao; }
    size_t getSize() const { return size; }
};
