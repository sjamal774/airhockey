#include "Draw.h"
#include "GameState.h"
#include <iostream>
SpriteRenderer* Renderer;
Window wind;

unsigned int VAO;
unsigned int shaderProgram;

void Draw::Render(GameState state, glm::vec2 bluepos, glm::vec2 redpos, glm::vec2 playersize,
                  int w, int h, glm::vec2 puckpos, glm::vec2 pucksize, int redscore,
                  int bluescore) {
  glm::vec2 scoreboardsize = glm::vec2(100.0f, 54.0f);
  glm::vec2 redscorepos = glm::vec2(15.0f, 0.0f);
  glm::vec2 bluescorepos = glm::vec2(w - 15.0f - scoreboardsize.x, 0.0f);

  if (state == GAME_ACTIVE) {
    // draw background
    Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f),
                         glm::vec2(w, h), 0.0f, glm::vec3(1.0f));
    Renderer->DrawSprite(ResourceManager::GetTexture("blueplayer"), bluepos, playersize, 0.0f,
                         glm::vec3(1.0f));
    Renderer->DrawSprite(ResourceManager::GetTexture("redplayer"), redpos, playersize, 0.0f,
                         glm::vec3(1.0f));
    Renderer->DrawSprite(ResourceManager::GetTexture("puck"), puckpos, pucksize, 0.0f,
                         glm::vec3(1.0f));

    PlayerScore(redscorepos, scoreboardsize, redscore);
    PlayerScore(bluescorepos, scoreboardsize, bluescore);

  } else if (state == GAME_WIN) {
    Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f),
                         glm::vec2(w, h), 0.0f, glm::vec3(1.0f));
    Renderer->DrawSprite(ResourceManager::GetTexture("blueplayer"), bluepos, playersize, 0.0f,
                         glm::vec3(1.0f));
    Renderer->DrawSprite(ResourceManager::GetTexture("redplayer"), redpos, playersize, 0.0f,
                         glm::vec3(1.0f));
    Renderer->DrawSprite(ResourceManager::GetTexture("gameover"),
                         glm::vec2(w / 2.0f - 356.0 / 2.0f, h / 2.0f - 259 / 2.0f),
                         glm::vec2(356.0f, 259.0f), 0.0f, glm::vec3(1.0f));

    PlayerScore(redscorepos, scoreboardsize, redscore);
    PlayerScore(bluescorepos, scoreboardsize, bluescore);
  }
}

void Draw::PlayerScore(glm::vec2 scorepos, glm::vec2 scoresize, int score) {
  if (score == 0) {
    Renderer->DrawSprite(ResourceManager::GetTexture("zero"), scorepos, scoresize, 0.0f,
                         glm::vec3(1.0f));
  } else if (score == 1) {
    Renderer->DrawSprite(ResourceManager::GetTexture("one"), scorepos, scoresize, 0.0f,
                         glm::vec3(1.0f));
  } else if (score == 2) {
    Renderer->DrawSprite(ResourceManager::GetTexture("two"), scorepos, scoresize, 0.0f,
                         glm::vec3(1.0f));
  } else if (score == 3) {
    Renderer->DrawSprite(ResourceManager::GetTexture("three"), scorepos, scoresize, 0.0f,
                         glm::vec3(1.0f));
  } else if (score == 4) {
    Renderer->DrawSprite(ResourceManager::GetTexture("four"), scorepos, scoresize, 0.0f,
                         glm::vec3(1.0f));
  } else if (score == 5) {
    Renderer->DrawSprite(ResourceManager::GetTexture("five"), scorepos, scoresize, 0.0f,
                         glm::vec3(1.0f));
  }
}

void Draw::Loading(int w, int h) {
  // load shaders
  ResourceManager::LoadShader("../../libs/gfx/shaders/background.vs",
                              "../../libs/gfx/shaders/background.fs", nullptr, "back");
  // configure shaders
  glm::mat4 proj =
      glm::ortho(0.0f, static_cast<float>(w), static_cast<float>(h), 0.0f, -1.0f, 1.0f);
  ResourceManager::GetShader("back").Use().SetInteger("image", 0);
  ResourceManager::GetShader("back").SetMatrix4("projection", proj);

  // set render-specific controls
  Renderer = new SpriteRenderer(ResourceManager::GetShader("back"));

  // load textures
  ResourceManager::LoadTexture("../../libs/gfx/resources/arena.png", true, "background");
  ResourceManager::LoadTexture("../../libs/gfx/resources/blue.png", true, "blueplayer");
  ResourceManager::LoadTexture("../../libs/gfx/resources/red.png", true, "redplayer");
  ResourceManager::LoadTexture("../../libs/gfx/resources/puck.png", true, "puck");
  ResourceManager::LoadTexture("../../libs/gfx/resources/gameover.png", true, "gameover");
  ResourceManager::LoadTexture("../../libs/gfx/resources/zeroscore.png", true, "zero");
  ResourceManager::LoadTexture("../../libs/gfx/resources/onescore.png", true, "one");
  ResourceManager::LoadTexture("../../libs/gfx/resources/twoscore.png", true, "two");
  ResourceManager::LoadTexture("../../libs/gfx/resources/threescore.png", true, "three");
  ResourceManager::LoadTexture("../../libs/gfx/resources/fourscore.png", true, "four");
  ResourceManager::LoadTexture("../../libs/gfx/resources/fivescore.png", true, "five");
}

void Draw::Polling() { glfwPollEvents(); }

void Draw::LoadRainbowRect() {
  // load stuff

  const char* vertexShaderSource =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "out vec4 vertexColor;\n"
      "void main()\n"
      "{\n"
      " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      " vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
      "}\0";

  const char* fragmentShaderSource =
      "#version 330 core\n"
      "out vec4 FragColor;\n"
      "uniform vec4 ourColor;\n"
      "void main()\n"
      "{\n"
      "FragColor = ourColor;\n"
      "}\n\0";

  float vertices[] = {
      1.0f,  1.0f,  0.0f,  // top right
      1.0f,  -1.0f, 0.0f,  // bottom right
      -1.0f, -1.0f, 0.0f,  // bottom left
      -1.0f, 1.0f,  0.0f   // top left
  };
  unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3,  // first triangle
      1, 2, 3   // second triangle
  };

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  unsigned int EBO;
  glGenBuffers(1, &EBO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);

  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // draw it
}

void Draw::DrawRainbowRect(float t) {
  glUseProgram(shaderProgram);

  float redValue = sin(t) * 0.75f + 0.5f;           // sin wave: 0 to 1
  float greenValue = sin(t + 2.0f) * 0.75f + 0.5f;  // phase shifted
  float blueValue = sin(t + 4.0f) * 0.75f + 0.5f;   // phase shifted further

  float pastelRed = redValue * 0.2f + 0.8f;      // 0.4/0.6 gives a cute retro feel
  float pastelGreen = greenValue * 0.2f + 0.8f;  // 0.3/0.7 was muted
  float pastelBlue = blueValue * 0.2f + 0.8f;

  int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
  glUniform4f(vertexColorLocation, pastelRed, pastelGreen, pastelBlue, 1.0f);

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
