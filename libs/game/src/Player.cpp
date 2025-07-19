#include "Player.h"
#include <iostream>

Player::Player(bool b, int w, int h) {
  Size = glm::vec2(80.0f, 80.0f);
  Radius = Size.x / 2.0f;
  score = 0;
  isBlue = b;
  Speed = 200.0f;
  width = w;
  height = h;
  if (isBlue) {
    Position = glm::vec2(width - Size.x - 185.0f, height / 2.0f - Size.y / 2.0f);
  } else {
    Position = glm::vec2(185.0f, height / 2.0f - Size.y / 2.0f);
  }
}

glm::vec2 Player::GetPosition() { return Position; }

glm::vec2 Player::GetSize() { return Size; }

void Player::Reset() {
  if (isBlue) {
    Position = glm::vec2(width - Size.x - 185.0f, height / 2.0f - Size.y / 2.0f);
  } else {
    Position = glm::vec2(185.0f, height / 2.0f - Size.y / 2.0f);
  }

  IsPressing = false;
}

int Player::GetScore() { return score; }
