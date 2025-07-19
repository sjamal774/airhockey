#ifndef BALL_H
#define BALL_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Ball {
 public:
  Ball(int w, int h);

  glm::vec2 GetPosition();
  glm::vec2 GetSize();
  glm::vec2 GetVelocity();
  glm::vec2 Position, Size;
  glm::vec2 Velocity = glm::vec2(0.0f, 0.0f);
  float Radius;
  float puckSpeed = 0.0f;
  void Reset();

 private:
  int width, height;
};

#endif