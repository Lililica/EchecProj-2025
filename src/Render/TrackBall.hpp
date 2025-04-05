#pragma once

#include "glm/ext/matrix_float4x4.hpp"

class TrackballCamera {
private:
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;

public:
    TrackballCamera() = default;
    TrackballCamera(float distance, float angleX, float angleY)
        : m_fDistance(distance), m_fAngleX(angleX), m_fAngleY(angleY) {};
    ~TrackballCamera() = default;

    void moveFront(float delta) { m_fDistance += delta; }
    void rotateLeft(float degrees) { m_fAngleY += degrees; }
    void rotateUp(float degrees) { m_fAngleX += degrees; }

    glm::mat4 getViewMatrix() const;
    glm::vec3 getPosition() const;
};