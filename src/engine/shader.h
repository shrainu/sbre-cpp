#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>


bool setUniformMat4f(GLuint shader, const std::string& name, glm::mat4 matrix);
bool setUniform4f(GLuint shader, const std::string& name, glm::vec4 floats);

std::string parseShader(const std::string& shaderSource);
GLuint compileShader(unsigned int type, const std::string& source);
GLuint createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
