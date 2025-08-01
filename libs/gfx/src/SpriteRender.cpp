#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader &shader) {
  this->shader = shader;
  this->initRenderData();
}

SpriteRenderer::~SpriteRenderer() { glDeleteVertexArrays(1, &this->quadVAO); }

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size,
                                float rotate, glm::vec3 color) {
  // prepare transformations
  shader.Use();
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(position, 0.0f));
  model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5 * size.y, 0.0));
  model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0, 0.0, 1.0));
  model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0));
  model = glm::scale(model, glm::vec3(size, 1.0f));
  shader.SetMatrix4("model", model);
  shader.SetVector3f("spriteColor", color);
  glActiveTexture(GL_TEXTURE0);
  texture.Bind();
  glBindVertexArray(quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void SpriteRenderer::initRenderData() {
  // configure VAO/VBO
  unsigned int VBO;
  float vertices[] = {
      // First triangle
      0.0f, 1.0f, 0.0f, 1.0f,  // top-left
      1.0f, 0.0f, 1.0f, 0.0f,  // bottom-right
      0.0f, 0.0f, 0.0f, 0.0f,  // bottom-left

      // Second triangle
      0.0f, 1.0f, 0.0f, 1.0f,  // top-left
      1.0f, 1.0f, 1.0f, 1.0f,  // top-right
      1.0f, 0.0f, 1.0f, 0.0f   // bottom-right
  };

  glGenVertexArrays(1, &this->quadVAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(this->quadVAO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

float clamp(float value, float min, float max) { return std::max(min, std::min(max, value)); }
