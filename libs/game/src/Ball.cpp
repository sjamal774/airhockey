#include "Ball.h"
#include <iostream>

Ball::Ball(int w, int h) {
  width = w;
  height = h;

  Size = glm::vec2(65.0f, 65.0f);  // 80 before
  Position = glm::vec2(w / 2.0f - Size.x / 2.0f,
                       h / 2.0f - Size.y / 2.0f);  // glm::vec2(w / 2.0f - Size.x / 2, h / 2.0f -
                                                   // Size.y / 2);
  Velocity = glm::vec2(0.0f, 0.0f);
  Radius = Size.x / 2.0f;
}

glm::vec2 Ball::GetPosition() { return Position; }

glm::vec2 Ball::GetSize() { return Size; }

glm::vec2 Ball::GetVelocity() { return Velocity; }

void Ball::Reset() {
  Position = glm::vec2(width / 2.0f - Size.x / 2.0f,
                       height / 2.0f - Size.y / 2.0f);  // glm::vec2(w / 2.0f - Size.x / 2, h
                                                        // / 2.0f - Size.y / 2);
  Velocity = glm::vec2(0.0f, 0.0f);
  puckSpeed = 0;
}
