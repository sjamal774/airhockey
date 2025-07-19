#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
 public:
  Window();
  void Initialize();
  void InitializeViewing();
  bool ShouldWindowClose();
  float GetDeltaTime(float a, float b);
  void Clear();
  void SwappingBuffers();
  void TerminatingGraphics();
  int GetScrWidth() const;
  int GetScrHeight() const;
  int GetFbw();
  int GetFbh();

  int fbw;
  int fbh;
  GLFWwindow* GetWindow();
};

#endif  // WINDOW_H