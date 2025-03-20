#pragma once

#include <glad/glad.h>
#include <glfw/src/internal.h>
#include <string>
#include "MyLibs/glimac/Image.hpp"

class Texture {
private:
    GLuint texture{};

public:
    Texture() = default;
    Texture(const std::string& path)
    {
        std::unique_ptr<glimac::Image>
            img = glimac::loadImage(path);
        if (img == nullptr)
            std::cerr << "Error loading image" << '\n';

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_RGBA, GL_FLOAT, img->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    };
    ~Texture()
    {
        glDeleteTextures(1, &texture);
    };
};