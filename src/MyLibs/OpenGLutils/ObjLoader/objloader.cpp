#include "objloader.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../../tinyobj/tiny_obj_loader.h"

std::vector<Vertex> ObjLoader::loaderObj()
{
    std::vector<Vertex> v;

    tinyobj::attrib_t                attributes;
    std::vector<tinyobj::shape_t>    shapes;
    std::vector<tinyobj::material_t> materials;
    std::string                      warnings;
    std::string                      errors;
    std::string                      modelPath       = path;
    std::string                      modelMtlBaseDir = "/Users/lililica/Documents/IMAC/Semestre4/EchecProj-2025/assets/";

    tinyobj::LoadObj(&attributes, &shapes, &materials, &warnings, &errors, modelPath.c_str(), modelMtlBaseDir.c_str());

    for (int i = 0; i < shapes.size(); i++)
    {
        tinyobj::shape_t& shape = shapes[i];
        tinyobj::mesh_t&  mesh  = shape.mesh;
        // we could visit the mesh index by using mesh.indices
        for (int j = 0; j < mesh.indices.size(); j++)
        {
            tinyobj::index_t i        = mesh.indices[j];
            glm::vec3        position = {
                attributes.vertices[i.vertex_index * 3],
                attributes.vertices[i.vertex_index * 3 + 1],
                attributes.vertices[i.vertex_index * 3 + 2]
            };
            glm::vec3 normal = glm::vec3(0.);
            if (i.normal_index >= 0)
                normal = {
                    attributes.normals[i.normal_index * 3],
                    attributes.normals[i.normal_index * 3 + 1],
                    attributes.normals[i.normal_index * 3 + 2]
                };
            glm::vec2 texCoord = glm::vec2(0.);
            if (i.texcoord_index >= 0)
            {
                texCoord = {
                    attributes.texcoords[i.texcoord_index * 2],
                    attributes.texcoords[i.texcoord_index * 2 + 1]
                };
            }
            // Not gonna care about texCoord right now.
            v.push_back(Vertex{position, normal, texCoord});
        }
    }

    return v;
}