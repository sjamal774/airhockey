#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"
// #include "resource_manager.h"
#include <iostream>

unsigned int SCREEN_WIDTH = 848;
unsigned int SCREEN_HEIGHT = 600;
GLFWwindow* window = nullptr;

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

Window::Window() {}

// here da f da function
//------------------------
int Window::GetScrWidth() const { return SCREEN_WIDTH; }

int Window::GetScrHeight() const { return SCREEN_HEIGHT; }

GLFWwindow* Window::GetWindow() { return window; }

void Window::Initialize() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  glfwWindowHint(GLFW_RESIZABLE, false);

  window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "air hockey", nullptr, nullptr);

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }
}

void Window::InitializeViewing() {
  glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

  int fbW, fbH;
  glfwGetFramebufferSize(window, &fbW, &fbH);

  glViewport(0, 0, fbW, fbH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  fbw = fbW;
  fbh = fbH;
}

bool Window::ShouldWindowClose() { return glfwWindowShouldClose(window); }

float Window::GetDeltaTime(float deltat, float lastf) {
  float currentFrame = glfwGetTime();
  deltat = currentFrame - lastf;
  lastf = currentFrame;
  glfwPollEvents();
  return deltat;
}

void Window::Clear() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Window::SwappingBuffers() { glfwSwapBuffers(window); }

void Window::TerminatingGraphics() { glfwTerminate(); }

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width and
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
