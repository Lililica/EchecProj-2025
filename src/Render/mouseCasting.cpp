#include "mouseCasting.hpp"
#include <algorithm>

// Fonction pour obtenir le rayon à partir de la souris
glm::vec3 getRayFromMouse(float mouseX, float mouseY, int screenWidth, int screenHeight, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
    // Conversion en coordonnées normalisées
    float     x        = (2.0f * mouseX) / screenWidth - 1.0f;
    float     y        = 1.0f - (2.0f * mouseY) / screenHeight;
    glm::vec4 ray_clip = glm::vec4(x, y, -1.0f, 1.0f);

    // Transformation en coordonnées caméra
    glm::vec4 ray_eye = glm::inverse(projectionMatrix) * ray_clip;
    ray_eye           = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);

    // Transformation en coordonnées monde
    glm::vec3 ray_world = glm::vec3(glm::inverse(viewMatrix) * ray_eye);
    ray_world           = glm::normalize(ray_world);

    return ray_world;
}

// Fonction d'intersection Rayon - AABB (boîte 3D)
bool rayIntersectsAABB(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3 boxMin, glm::vec3 boxMax, float& tHit)
{
    float tMin = (boxMin.x - rayOrigin.x) / rayDirection.x;
    float tMax = (boxMax.x - rayOrigin.x) / rayDirection.x;

    if (tMin > tMax)
        std::swap(tMin, tMax);

    float tyMin = (boxMin.y - rayOrigin.y) / rayDirection.y;
    float tyMax = (boxMax.y - rayOrigin.y) / rayDirection.y;

    if (tyMin > tyMax)
        std::swap(tyMin, tyMax);

    if ((tMin > tyMax) || (tyMin > tMax))
        return false;

    tMin = std::max(tyMin, tMin);
    tMax = std::min(tyMax, tMax);

    float tzMin = (boxMin.z - rayOrigin.z) / rayDirection.z;
    float tzMax = (boxMax.z - rayOrigin.z) / rayDirection.z;

    if (tzMin > tzMax)
        std::swap(tzMin, tzMax);

    if ((tMin > tzMax) || (tzMin > tMax))
        return false;

    tMin = std::max(tzMin, tMin);
    tMax = std::min(tzMax, tMax);

    if (tMin > tHit)
        return false;

    tHit = tMin;
    return true;
}