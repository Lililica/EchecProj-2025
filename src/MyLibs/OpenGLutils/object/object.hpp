#pragma once
#include <string>
#include "texture.hpp"
#include "vertexUtils.hpp"

class Object {
private:
    VAO     vao;
    Texture texture;

public:
    Object()  = default;
    ~Object() = default;

    VAO*     getVAO() { return &vao; }
    Texture* getTexture() { return &texture; }

    void obj_loader(std::string const& path_texture, std::string const& path_obj)
    {
        vao.init_vao(path_obj);
        texture = Texture(path_texture);
    }
};
