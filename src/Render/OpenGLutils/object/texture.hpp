#pragma once

#include "MyLibs/stb_image/stb_image.h"
#include <glad/glad.h>
#include <glfw/src/internal.h>
#include <iostream>
#include <string>

class Texture {
private:
  GLuint texture{};

public:
  Texture() = default;
  ~Texture() {
    std::cout << "Texture deleted" << std::endl;
    glDeleteTextures(1, &texture);
  };

  void init_texture(const std::string &path) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int width, height, nrChannels;
    unsigned char *data =
        stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
      stbi_set_flip_vertically_on_load(false);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, data);
      stbi_image_free(data);
    } else {
      std::cout << "Failed to load texture: " << path << std::endl;
      stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
  };

  GLuint getTexture() const { return texture; };
};