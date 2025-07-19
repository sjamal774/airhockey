#ifndef DRAW_H
#define DRAW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Window.h"
#include "GameState.h"

class Draw {
 public:
  void Render(GameState state, glm::vec2 bpos, glm::vec2 rpos, glm::vec2 playersize, int w, int h,
              glm::vec2 puckpos, glm::vec2 pucksize, int redscore, int bluescore);
  static void Loading(int w, int h);
  void DrawRainbowRect(float t);
  void LoadRainbowRect();
  void Polling();
  void PlayerScore(glm::vec2 pos, glm::vec2 size, int score);
};

#endif