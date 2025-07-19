#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GameState.h"
#include "Draw.h"
#include "Player.h"
#include "Ball.h"
#include "Window.h"

// Represents the current state of the game

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.

const float PLAYER_VELOCITY(500.0f);
enum Direction { UP, RIGHT, DOWN, LEFT, UPRIGHT, DOWNRIGHT, UPLEFT, DOWNLEFT };
typedef std::tuple<bool, Direction, glm::vec2> Collision;

namespace game {
class Game {
 public:
  // game state

  GameState State;
  bool Keys[1024];

  // constructor/destructor
  Game(unsigned int width, unsigned int height);
  // initialize game state (load all shaders/textures/levels)
  void Init();
  // game loop
  void ProcessInput(float dt);
  void DoCollisions();
  void DoACollision(Player &a);
  Player GetPlayerBlue();
  Player GetPlayerRed();
  GameState GetState();
  void Update(float dt);
  void ClampPlayer(glm::vec2 &pos, Player &a, bool isBlue);
  bool Clamp(glm::vec2 &pos, float xmin, float xmax, float ymin, float ymax);
  void MovePlayer(glm::vec2 dir, float dt, Player &a);

  void Reset();
  Ball GetBall();
  Collision CheckCollision(Ball &one, Player &two);

 private:
  Window wind;
  Player blue;
  Player red;
  Ball puck;
  const int finalscore = 5;
  const float ACCEL = 700.0f;
  const float MAX_SPEED = 1000.0f;
  const float FRICTION = 250.0f;
  const float GOAL_POST_OFFSET = 160.0f;
  float INITIAL_SPEED = 500.0f;
  float PLAYER_FORCE = 1.5f;
  int Width, Height;
};
}  // namespace game

#endif