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

  void moveFront(float delta) {
    delta < 0 ? (m_fDistance < 10 ?: m_fDistance += delta)
              : m_fDistance += delta;
  }
  void rotateLeft(float degrees) { m_fAngleY += degrees; }
  void rotateUp(float degrees) {
    if (m_fAngleX >= 60 && degrees > 0)
      m_fAngleX = 60;
    else if (m_fAngleX <= 0 && degrees < 0)
      m_fAngleX = 0;
    else
      m_fAngleX += degrees;
  }

  glm::mat4 getViewMatrix() const;
  glm::vec3 getPosition() const;
};