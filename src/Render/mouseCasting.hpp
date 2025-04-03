#pragma once

#include <glm/glm.hpp>

glm::vec3 getRayFromMouse(float mouseX, float mouseY, int screenWidth, int screenHeight, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

bool rayIntersectsAABB(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3 boxMin, glm::vec3 boxMax, float& tHit);