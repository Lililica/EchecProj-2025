#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <glad/glad.h>
#include "MyLibs/glimac/Program.hpp"

class ShaderLoader {
private:
    glimac::Program program{};

public:
    ShaderLoader()  = default;
    ~ShaderLoader() = default;

    glimac::Program* getProgram() { return &program; }

    void loadShaders(const char* vertex_file_path, const char* fragment_file_path)
    {
        program =
            glimac::loadProgram(vertex_file_path, fragment_file_path);
        program.use();
    };
};

#endif
