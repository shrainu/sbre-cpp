#include "engine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <iostream>


GLFWwindow* initEngine(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* TITLE, int VSync) {

    // Initialize GLFW
    if(!glfwInit()) {
        std::cout << "[GLFW Error][GLFW could not be initialized!]\n";
        return nullptr;
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE, NULL, NULL);
    if (!window) {
        std::cout << "[GLFW Error][Window could now be initialized!]\n";
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    // Enable-Disable V-Sync
    glfwSwapInterval(VSync);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cout << "[GLEW Error][GLEW could not be initialized!]\n";
        glfwTerminate();
        return nullptr;
    }

    // Enable Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return window;
}

void terminateEngine() {

    glfwTerminate();
}

void initImGui(GLFWwindow* window) {

    // Initialize ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void terminateImGui() {

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}