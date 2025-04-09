#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include "MyLibs/glimac/Program.hpp"
#include <glad/glad.h>

class ShaderLoader {
private:
  glimac::Program program{};

public:
  ShaderLoader() = default;
  ~ShaderLoader() {
    // Cleanup
    glDeleteProgram(program.getGLId());
    std::cout << "Shader deleted" << std::endl;
  };

  glimac::Program *getProgram() { return &program; }

  void loadShaders(const char *vertex_file_path,
                   const char *fragment_file_path) {
    program = glimac::loadProgram(vertex_file_path, fragment_file_path);
  };

  void useProgram() { program.use(); };
};

#endif
