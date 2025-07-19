#include "Game.h"
#include "Window.h"
#include "Draw.h"
#include "Player.h"
#include "miniaudio.h"
#include <iostream>

game::Game* GlobalGame = nullptr;

void InitAndPlayMusic(const char* filepath);
void ShutdownMusic();

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
  if (key >= 0 && key < 1024 && GlobalGame) {
    if (action == GLFW_PRESS)
      GlobalGame->Keys[key] = true;
    else if (action == GLFW_RELEASE)
      GlobalGame->Keys[key] = false;
  }
}

int main() {
  Window wind;
  Draw drawing;
  int width = wind.GetScrWidth();
  int height = wind.GetScrHeight();
  game::Game airHockey(width, height);
  GlobalGame = &airHockey;

  wind.Initialize();
  glfwSetKeyCallback(wind.GetWindow(), KeyCallback);
  wind.InitializeViewing();
  airHockey.Init();

  drawing.LoadRainbowRect();

  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  InitAndPlayMusic("../../libs/gfx/resources/goldenrod.mp3");

  while (!wind.ShouldWindowClose()) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    drawing.Polling();

    airHockey.ProcessInput(deltaTime);
    airHockey.Update(deltaTime);

    wind.Clear();

    float timeValue = glfwGetTime();
    drawing.DrawRainbowRect(timeValue);
    drawing.Render(airHockey.GetState(), airHockey.GetPlayerBlue().GetPosition(),
                   airHockey.GetPlayerRed().GetPosition(), airHockey.GetPlayerBlue().GetSize(),
                   width, height, airHockey.GetBall().GetPosition(), airHockey.GetBall().GetSize(),
                   airHockey.GetPlayerRed().GetScore(), airHockey.GetPlayerBlue().GetScore());
    wind.SwappingBuffers();
  }

  ShutdownMusic();

  ResourceManager::Clear();
  wind.TerminatingGraphics();
}
