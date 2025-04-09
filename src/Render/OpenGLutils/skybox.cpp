#include "skybox.hpp"
#include "MyLibs/stb_image/stb_image.h"
#include <glad/glad.h>
#include <iostream>

void Skybox::init_Vertex() {

  // Generate and bind the VAO, VBO, and EBO for the skybox
  glGenVertexArrays(1, &skyboxVAO);
  glGenBuffers(1, &skyboxVBO);
  glGenBuffers(1, &skyboxEBO);

  glBindVertexArray(skyboxVAO);

  glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * skyboxVertices.size(),
               skyboxVertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(unsigned int) * skyboxIndices.size(),
               skyboxIndices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  //   Unbind the VBO and EBO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind the VAO
}

void Skybox::init_Texture() {

  // Creates the cubemap texture object

  glGenTextures(1, &cubemapTexture);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  // Cycles through all the textures and attaches them to the cubemap object
  for (unsigned int i = 0; i < 6; i++) {
    int width, height, nrChannels;
    unsigned char *data =
        stbi_load(facesTextures[i].c_str(), &width, &height, &nrChannels, 0);
    if (data) {
      stbi_set_flip_vertically_on_load(false);
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height,
                   0, GL_RGB, GL_UNSIGNED_BYTE, data);
      stbi_image_free(data);
    } else {
      std::cout << "Failed to load texture: " << facesTextures[i] << std::endl;
      stbi_image_free(data);
    }
  }

  glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

  std::cout << "Skybox texture loaded : " << cubemapTexture << std::endl;
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  //   glBindTexture(GL_TEXTURE_2D, 0);
}
