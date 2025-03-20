#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"

class Vertex {
public:
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

class ObjLoader {
private:
    std::string path;

public:
    ObjLoader() = default;
    explicit ObjLoader(std::string p)
        : path(std::move(p)) {}
    ~ObjLoader() = default;

    std::vector<Vertex> loaderObj();
};