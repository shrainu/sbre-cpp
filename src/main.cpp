#include "engine/engine.h"
#include "engine/shader.h"
#include "engine/renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <iostream>
#include <array>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <array>


int main() {

    // Initialzie OpenGL
    GLFWwindow* window = initEngine(SCREEN_WIDTH, SCREEN_HEIGHT, "Untitled Game");

    // Initialize ImGUI
    initImGui(window);

    // Create shader program
    GLuint shader = createShaderProgram("../res/shader/base/vertex.glsl",
                                        "../res/shader/base/fragment.glsl");

    // Model View Projection Matrix
    glm::mat4 proj = glm::ortho(0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f, -1.0f, 1.0f);
    glm::mat4 mvp = proj;

    // Initialize batch renderer
    initRenderer(shader);

    while (!glfwWindowShouldClose(window)) {

        // Calculate FPS
 		calculateFPS();       

        // Calculate delta time;
        calculateDeltaTime();

        // Render Loop
        glClearColor(0.2f, 0.05f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Begin the render batch
        resetBatchStats();
        beginBatch();

        glUseProgram(shader);
        setUniformMat4f(shader, "u_mvp", mvp);

        // End the render batch
        endBatch();
        renderBatch();

        // Draw GUI
		drawPerformanceGUI();

        // End render loop
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    terminateImGui();
    terminateRenderer();
    terminateEngine(); 
    return 0;
}