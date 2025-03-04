#include "objloader.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../tinyobj/tiny_obj_loader.h"

std::vector<GLfloat> ObjLoader::loaderObj()
{
    std::vector<GLfloat> verticesFin;

    if (listPath.size() == 0)
        return verticesFin;

    for (auto& path : listPath)
    {
        tinyobj::attrib_t                attributes;
        std::vector<tinyobj::shape_t>    shapes;
        std::vector<tinyobj::material_t> materials;
        std::string                      warnings;
        std::string                      errors;
        std::string                      modelPath       = path;
        std::string                      modelMtlBaseDir = "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/";

        tinyobj::LoadObj(&attributes, &shapes, &materials, &warnings, &errors, modelPath.c_str(), modelMtlBaseDir.c_str());

        for (float& vertices : attributes.vertices)
        {
            verticesFin.push_back(vertices);
        }
    }

    return verticesFin;
}