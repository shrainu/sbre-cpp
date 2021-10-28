#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"


inline constexpr int SCREEN_WIDTH  = 960;
inline constexpr int SCREEN_HEIGHT = 680;
inline constexpr int PIXEL_SIZE  = 5;

inline constexpr uint32_t MAX_QUAD = 10000;
inline constexpr uint32_t MAX_VERTEX = MAX_QUAD * 4;
inline constexpr uint32_t MAX_INDEX = MAX_QUAD * 6;

extern int32_t MAX_TEXTURE_SLOTS;

extern double deltaTime;


void drawPerformanceGUI();
void drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
void drawTexture(const glm::vec2& pos, const glm::vec2& size, Texture* text);

void calculateFPS();
void calculateDeltaTime();
glm::vec3 convertHSVtoRGB(int h, float s, float v, bool normalized = false);
glm::vec2 getMousePos(GLFWwindow* window);

void initRenderer(GLuint shader);
void resetBatchStats();
void beginBatch();
void endBatch();
void renderBatch();
void terminateRenderer();
