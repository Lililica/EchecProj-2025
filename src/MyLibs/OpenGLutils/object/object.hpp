#pragma once
#include <string>
#include "glm/ext/vector_float2.hpp"
#include "texture.hpp"
#include "vertexUtils.hpp"

class Object {
private:
    VAO     vao;
    Texture texture;

public:
    Object(std::string const& path_texture, std::string const& path_obj)
    {
        vao     = VAO(path_obj);
        texture = Texture(path_texture);
    };
    ~Object() = default;

    VAO     getVAO() { return vao; }
    Texture getTexture() { return texture; }
};