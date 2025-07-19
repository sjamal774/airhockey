#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Player {
 public:
  Player(bool isBlue, int w, int h);
  glm::vec2 Position, Size, Velocity;
  int score;
  bool isBlue;
  int width, height;
  float Radius;
  float Speed;
  bool IsPressing = false;

  glm::vec2 GetPosition();
  glm::vec2 GetSize();
  int GetScore();
  void Reset();
};

#endif