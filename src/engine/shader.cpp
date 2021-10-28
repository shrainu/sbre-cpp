#include "shader.h"

#include <string>
#include <string.h>
#include <sstream>
#include <fstream>


bool setUniformMat4f(GLuint shader, const std::string& name, glm::mat4 matrix) {

    int location = glGetUniformLocation(shader, name.c_str());
    if (location == -1) {
        std::cout << "[OpenGL Warning][\"" << name << "\" is not a valid uniform location]\n";
        return false;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
    return true;
}

bool setUniform4f(GLuint shader, const std::string& name, glm::vec4 floats) {

    int location = glGetUniformLocation(shader, name.c_str());
    if (location == -1) {
        std::cout << "[OpenGL Warning][\"" << name << "\" is not a valid uniform location]\n";
        return false;
    }

    glUniform4f(location, floats.x, floats.y, floats.z, floats.w);
    return true;
}

GLuint createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {

    GLuint program = glCreateProgram();
    GLuint vs = compileShader(GL_VERTEX_SHADER, parseShader(vertexShaderSource));
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, parseShader(fragmentShaderSource));

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "[OpenGL Error][Shader program failed to link : \n" << infoLog << "]\n";
        return 0;
    }

    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


GLuint compileShader(GLuint type, const std::string& source) {

    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(shader, length, &length, message);
        std::cout << "[OpenGL Error][Shader failed to compile : "
                  << ((type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment") << "]\n";
        std::cout << "[LOG : " << message << "]\n";
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}


std::string parseShader(const std::string& shaderSource) {

    std::string line;
    std::fstream file(shaderSource);
    std::stringstream stream;

    while(getline(file, line)) {

        stream << line << '\n';
    }

    return stream.str();
}
