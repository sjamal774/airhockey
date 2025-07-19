#include "Game.h"
#include <iostream>
#include <algorithm>

game::Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE),
      Keys(),
      Width(width),
      Height(height),
      blue(true, width, height),
      red(false, width, height),
      puck(width, height) {}

void game::Game::Init() { Draw::Loading(Width, Height); }

void game::Game::ProcessInput(float dt) {
  if (State == GAME_ACTIVE) {
    glm::vec2 dirb(0.0f);
    if (Keys[GLFW_KEY_LEFT]) dirb.x -= 1.0f;
    if (Keys[GLFW_KEY_RIGHT]) dirb.x += 1.0f;
    if (Keys[GLFW_KEY_UP]) dirb.y -= 1.0f;
    if (Keys[GLFW_KEY_DOWN]) dirb.y += 1.0f;

    MovePlayer(dirb, dt, blue);

    glm::vec2 dirr(0.0f);
    if (Keys[GLFW_KEY_A]) dirr.x -= 1.0f;
    if (Keys[GLFW_KEY_D]) dirr.x += 1.0f;
    if (Keys[GLFW_KEY_W]) dirr.y -= 1.0f;
    if (Keys[GLFW_KEY_S]) dirr.y += 1.0f;

    MovePlayer(dirr, dt, red);

    if (this->Keys[GLFW_KEY_UP] || this->Keys[GLFW_KEY_DOWN] || this->Keys[GLFW_KEY_LEFT] ||
        this->Keys[GLFW_KEY_RIGHT]) {
      blue.IsPressing = true;
    } else {
      blue.IsPressing = false;
    }

    if (this->Keys[GLFW_KEY_A] || this->Keys[GLFW_KEY_S] || this->Keys[GLFW_KEY_D] ||
        this->Keys[GLFW_KEY_W]) {
      red.IsPressing = true;
    } else {
      red.IsPressing = false;
    }
  }

  if (this->Keys[GLFW_KEY_ENTER] && State == GAME_WIN) {
    Reset();
  }
}

void game::Game::Update(float dt) {
  if (red.score == finalscore || blue.score == finalscore) {
    State = GAME_WIN;
  }

  if (State == GAME_ACTIVE) {
    // // if puck is moving then only do we slow it down with friction
    // // //lets work with constant speeds for now
    if (puck.puckSpeed > 0) {
      puck.puckSpeed = std::max(puck.puckSpeed - FRICTION * dt, 0.0f);
      puck.Velocity = glm::normalize(puck.Velocity) * puck.puckSpeed;
    }

    // goal 1 region
    if (puck.Position.x + puck.Velocity.x * dt + puck.Size.x > Width &&
        puck.Position.y > GOAL_POST_OFFSET &&
        puck.Position.y + puck.Size.y < Height - GOAL_POST_OFFSET) {
      puck.Position += puck.Velocity * dt;
      if (puck.Position.x > Width) {
        red.score++;
        if (red.score != finalscore) {
          puck.Reset();
          blue.Reset();
          red.Reset();
        }
      }
    } else if (puck.Position.x + puck.Velocity.x * dt < 0 && puck.Position.y > GOAL_POST_OFFSET &&
               puck.Position.y + puck.Size.y < Height - GOAL_POST_OFFSET) {  // goal 2 region
      puck.Position += puck.Velocity * dt;
      if (puck.Position.x < 0) {
        blue.score++;
        if (blue.score != finalscore) {
          puck.Reset();
          blue.Reset();
          red.Reset();
        }
      }
    } else {  // making the puck bounce off
      if (puck.Position.x + puck.Velocity.x * dt > Width - puck.Size.x) {
        puck.Position.x = Width - puck.Size.x;
        puck.Velocity.x = -puck.Velocity.x;
      } else if (puck.Position.x + puck.Velocity.x * dt < 0) {
        puck.Position.x = 0;
        puck.Velocity.x = -puck.Velocity.x;
      } else {
        puck.Position.x += puck.Velocity.x * dt;
      }
      if (puck.Position.y + puck.Velocity.y * dt > Height - puck.Size.y) {
        puck.Position.y = Height - puck.Size.y;
        puck.Velocity.y = -puck.Velocity.y;
      } else if (puck.Position.y + puck.Velocity.y * dt < 0) {
        puck.Position.y = 0;
        puck.Velocity.y = -puck.Velocity.y;
      } else {
        puck.Position.y += puck.Velocity.y * dt;
      }
    }
  }

  DoCollisions();
}

void game::Game::DoCollisions() {
  DoACollision(blue);
  DoACollision(red);
}

void game::Game::DoACollision(Player& a) {
  Collision collision = CheckCollision(puck, a);

  if (std::get<0>(collision))  // if collision is true
  {
    // lets make them touch only at the edges
    glm::vec2 v = std::get<2>(collision);
    float dist = glm::length(v);
    float x = dist - puck.Radius;
    float penetration = a.Radius - x;

    glm::vec2 u = normalize(v);
    glm::vec2 scaledu = glm::vec2(penetration * u.x, penetration * u.y);
    glm::vec2 center = a.Position + glm::vec2(a.Radius);
    glm::vec2 newCenter = glm::vec2(center.x + scaledu.x, center.y + scaledu.y);
    glm::vec2 adjustedNewCenter = glm::vec2(newCenter.x - a.Radius, newCenter.y - a.Radius);
    a.Position.x = adjustedNewCenter.x;
    a.Position.y = adjustedNewCenter.y;
    ClampPlayer(a.Position, a, a.isBlue);

    // now we hit it
    if (a.IsPressing && a.Speed != 0 &&
        glm::dot(glm::normalize(a.Velocity), glm::normalize(puck.Velocity)) != -1) {
      puck.puckSpeed = PLAYER_FORCE * a.Speed;
      puck.Velocity = glm::vec2(puck.puckSpeed * -u.x, puck.puckSpeed * -u.y);
    } else {
      puck.Velocity = glm::reflect(puck.Velocity, u);
      puck.puckSpeed = glm::length(puck.Velocity);
      puck.Velocity = glm::normalize(puck.Velocity) * puck.puckSpeed;
    }
  }
}

void game::Game::MovePlayer(glm::vec2 dir, float dt, Player& a) {
  if (dir != glm::vec2(0.0f, 0.0f)) {
    dir = glm::normalize(dir);
  }
  // predicted values
  glm::vec2 x = a.Position;
  glm::vec2 v0 = a.Speed * dir;
  glm::vec2 xf = a.Position + v0 * dt + 0.5f * ACCEL * dir * dt * dt;
  ClampPlayer(xf, a, a.isBlue);
  float deltax = glm::length(xf - x);

  if (deltax != 0 && dir != glm::vec2(0.0f, 0.0f)) {
    if (a.Speed == 0.0f) {
      a.Speed = INITIAL_SPEED;
    } else {
      a.Speed = std::min(a.Speed + ACCEL * dt, MAX_SPEED);
    }
    glm::vec2 v0 = a.Speed * dir;
    glm::vec2 xf = a.Position + v0 * dt + 0.5f * ACCEL * dir * dt * dt;
    ClampPlayer(xf, a, a.isBlue);
  } else {
    glm::vec2 xf = x;
    a.Speed = 0.0f;
    a.Velocity = glm::vec2{0};
  }
  a.Position = xf;
}

void game::Game::ClampPlayer(glm::vec2& pos, Player& a, bool isBlue) {
  if (isBlue) {
    Clamp(pos, Width / 2.0f, Width - a.Size.x, 0.0f, Height - a.Size.y);
  } else {
    Clamp(pos, 0, Width / 2.0f - a.Size.x, 0.0f, Height - a.Size.y);
  }
}

bool game::Game::Clamp(glm::vec2& pos, float xmin, float xmax, float ymin, float ymax) {
  float newX = std::clamp(pos.x, xmin, xmax);
  float newY = std::clamp(pos.y, ymin, ymax);

  bool clipped = (newX != pos.x) | (newY != pos.y);
  pos.x = newX;
  pos.y = newY;
  return clipped;
}

Collision game::Game::CheckCollision(Ball& one, Player& two) {
  glm::vec2 centerA = one.Position + glm::vec2(one.Radius);
  glm::vec2 centerB = two.Position + glm::vec2(two.Radius);

  glm::vec2 difference = centerB - centerA;
  float distance = glm::length(difference);
  float radiusSum = one.Radius + two.Radius;

  if (distance <= radiusSum) {
    return std::make_tuple(true, UP, difference);
  } else {
    return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
  }
}

Ball game::Game::GetBall() { return puck; }

Player game::Game::GetPlayerBlue() { return blue; }

Player game::Game::GetPlayerRed() { return red; }

GameState game::Game::GetState() { return State; }

void game::Game::Reset() {
  blue.Reset();
  red.Reset();
  puck.Reset();
  blue.score = 0;
  red.score = 0;
  State = GAME_ACTIVE;
}
