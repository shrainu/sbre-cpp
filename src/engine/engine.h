#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


GLFWwindow* initEngine(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* TITLE, int VSync = 0);
void terminateEngine();
void initImGui(GLFWwindow* window);
void terminateImGui();