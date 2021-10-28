#include "renderer.h"

#include <math.h>
#include <string>
#include <string.h>
#include <sstream>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>


struct Vertex {

    glm::vec2 pos;
    glm::vec4 color;
    glm::vec2 texCoord;
    float texIndex;
};

struct RendererData {

    // Data
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;

    uint32_t indexCount = 0;

    Vertex* quadBuffer = nullptr;
    Vertex* quadBufferPtr = nullptr;

    // Default white texture
    Texture* defaultTexture;

    // Texture Slots
    GLuint* textureSlots;
    uint32_t textureIndex = 1;

    // Stats
    uint32_t renderCount = 0;
    uint32_t quadCount = 0;
};


// RenderData
RendererData rd = RendererData();

// Texture Slots
int32_t MAX_TEXTURE_SLOTS = 0;

// Deltatime variables
constexpr double deltaTimeHigh = 0.1;
static double lastFrameTime = 0.0;
static double crntFrameTime;
double deltaTime;

// FPS Counter variables
static double prevTime = 0.0;
static double crntTime = 0.0;
static double timeDiff;
static uint32_t fpsCounter = 0;
static std::string fps;
static std::string frameTime;


void drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color) {

    if (rd.indexCount >= MAX_INDEX) {
        endBatch();
        renderBatch();
        beginBatch();
    }

    float textureIndex = 0.0f;

    rd.quadBufferPtr->pos = {pos.x, pos.y};
    rd.quadBufferPtr->color = {color.r, color.g, color.b, color.a};
    rd.quadBufferPtr->texCoord = {0.0f, 1.0f};
    rd.quadBufferPtr->texIndex = textureIndex;
    rd.quadBufferPtr++;

    rd.quadBufferPtr->pos = {pos.x + size.x, pos.y};
    rd.quadBufferPtr->color = {color.r, color.g, color.b, color.a};
    rd.quadBufferPtr->texCoord = {1.0f, 1.0f};
    rd.quadBufferPtr->texIndex = textureIndex;
    rd.quadBufferPtr++;

    rd.quadBufferPtr->pos = {pos.x, pos.y + size.y};
    rd.quadBufferPtr->color = {color.r, color.g, color.b, color.a};
    rd.quadBufferPtr->texCoord = {0.0f, 0.0f};
    rd.quadBufferPtr->texIndex = textureIndex;
    rd.quadBufferPtr++;

    rd.quadBufferPtr->pos = {pos.x + size.x, pos.y + size.y};
    rd.quadBufferPtr->color = {color.r, color.g, color.b, color.a};
    rd.quadBufferPtr->texCoord = {1.0f, 0.0f};
    rd.quadBufferPtr->texIndex = textureIndex;
    rd.quadBufferPtr++;

    rd.indexCount += 6;
    rd.quadCount++;
}

void drawTexture(const glm::vec2& pos, const glm::vec2& size, Texture* text) {

    if (rd.indexCount >= MAX_INDEX || rd.textureIndex > MAX_TEXTURE_SLOTS) {
        endBatch();
        renderBatch();
        beginBatch();
    }

    float textureIndex = 0.0f;
    
    for (int i = 1; i < rd.textureIndex; ++i) {

        if (rd.textureSlots[i] == text->textureID) {
            textureIndex = (float)i;
            break;
        }
    }
    
    if (textureIndex == 0.0f) {

        textureIndex = (float)rd.textureIndex;
        rd.textureSlots[rd.textureIndex] = text->textureID;
        rd.textureIndex++;
    }
    
    glm::vec4 color = text->color;

    rd.quadBufferPtr->pos = {pos.x, pos.y};
    rd.quadBufferPtr->color = {color.r, color.g, color.b, color.a};
    rd.quadBufferPtr->texCoord = {0.0f, 1.0f};
    rd.quadBufferPtr->texIndex = textureIndex;
    rd.quadBufferPtr++;

    rd.quadBufferPtr->pos = {pos.x + size.x, pos.y};
    rd.quadBufferPtr->color = {color.r, color.g, color.b, color.a};
    rd.quadBufferPtr->texCoord = {1.0f, 1.0f};
    rd.quadBufferPtr->texIndex = textureIndex;
    rd.quadBufferPtr++;

    rd.quadBufferPtr->pos = {pos.x, pos.y + size.y};
    rd.quadBufferPtr->color = {color.r, color.g, color.b, color.a};
    rd.quadBufferPtr->texCoord = {0.0f, 0.0f};
    rd.quadBufferPtr->texIndex = textureIndex;
    rd.quadBufferPtr++;

    rd.quadBufferPtr->pos = {pos.x + size.x, pos.y + size.y};
    rd.quadBufferPtr->color = {color.r, color.g, color.b, color.a};
    rd.quadBufferPtr->texCoord = {1.0f, 0.0f};
    rd.quadBufferPtr->texIndex = textureIndex;
    rd.quadBufferPtr++;

    rd.indexCount += 6;
    rd.quadCount++;
}

void drawPerformanceGUI() {

	std::stringstream ss;
    ss << rd.renderCount;
    std::string drawCalls = "Render Call : " + ss.str();
    ss.str(std::string());
    ss << rd.quadCount;
    std::string quadCount = "Quad Count : " + ss.str();
    ss.str(std::string());
    ss << rd.textureIndex + 1;
    std::string textureCount = "Unique Texture Count : "  + ss.str();
    ImGui::Begin("Performance");
    ImGui::Text("%s", drawCalls.c_str());
    ImGui::Text("%s", quadCount.c_str());
    ImGui::Text("%s", textureCount.c_str());
    ImGui::Text("%s", std::string("FPS : " + fps).c_str());
    ImGui::Text("%s", std::string("Frame Time : " + frameTime).c_str());
    ImGui::End();
}

void calculateFPS() {

	crntTime = glfwGetTime();
    timeDiff = crntTime - prevTime;
    fpsCounter++;
    if (timeDiff >= 1 / 30.0) {
		fps = std::to_string((1.0 / timeDiff) * fpsCounter);
        frameTime = std::to_string((timeDiff / fpsCounter) * 1000);
        prevTime = crntTime;
		fpsCounter = 0;
    }
}

void calculateDeltaTime() {

    crntFrameTime = glfwGetTime();
    deltaTime = crntFrameTime - lastFrameTime;
    if (deltaTime > deltaTimeHigh)
        deltaTime = deltaTimeHigh;
    lastFrameTime = crntFrameTime;
}

glm::vec3 convertHSVtoRGB(int h, float s, float v, bool normalized) {

	float c = s * v;
	float x = c * (1 - fabs((fmod((h / 60.0), 2.0)) - 1));
	float m = v - c;

	float r_, g_, b_;
	
	if      (0 <= h && h < 60) {
		r_ = c;
		g_ = x;
		b_ = 0;	
	}
	else if (60 <= h && h < 120) {
		r_ = x;
		g_ = c;
		b_ = 0;
	}
	else if (120 <= h && h < 180) {
		r_ = 0;
		g_ = c;
		b_ = x;
	}
	else if (180 <= h && h < 240) {
		r_ = 0;
		g_ = x;
		b_ = c;
	}
	else if (240 <= h && h < 300) {
		r_ = x;
		g_ = 0;
		b_ = c;
	}
	else if (300 <= h && h < 360) {
		r_ = c;
		g_ = 0;
		b_ = x;
	}

	int r = round((r_ + m) * 255);
	int g = round((g_ + m) * 255);
	int b = round((b_ + m) * 255);

	if (!normalized)
		return {r, g, b};

	return {r / 255.0f, g / 255.0f, b / 255.0f};
}

glm::vec2 getMousePos(GLFWwindow* window) {

    const bool reverse = false;

    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    if (reverse)
        return { xPos, (SCREEN_HEIGHT - yPos) };
    else
        return { xPos, yPos };
}

void initRenderer(GLuint shader) {

    // Set samplers to default
    glUseProgram(shader);
    int samplers[16];
    for (int i = 0; i < 16; ++i) {
        samplers[i] = i;
    }
    int32_t loc = glGetUniformLocation(shader, "u_textures");
    glUniform1iv(loc, 16, samplers);

    // Initialize the renderer
    rd.quadBuffer = new Vertex[MAX_VERTEX];

    glGenVertexArrays(1, &rd.vao);
    glBindVertexArray(rd.vao);

    glGenBuffers(1, &rd.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, rd.vbo);
    glBufferData(GL_ARRAY_BUFFER, MAX_VERTEX * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texIndex));
    glEnableVertexAttribArray(3);

    uint32_t indices[MAX_INDEX];
    uint32_t offset = 0;
    for (uint32_t i = 0; i < MAX_INDEX; i += 6) {

        indices[0 + i] = 0 + offset;
        indices[1 + i] = 1 + offset;
        indices[2 + i] = 2 + offset;
        indices[3 + i] = 2 + offset;
        indices[4 + i] = 3 + offset;
        indices[5 + i] = 1 + offset;

        offset += 4;
    }

    glGenBuffers(1, &rd.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rd.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set the MAX_TEXTURE_SLOTS avalible in this machine
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &MAX_TEXTURE_SLOTS);

    // Allocate memory for texture slots
    rd.textureSlots = new GLuint[MAX_TEXTURE_SLOTS];

    // Generate Default White texture
    rd.defaultTexture = loadTexture("../res/sprite/default_sprite.png");
    rd.textureSlots[0] = rd.defaultTexture->textureID;
    for (int i = rd.textureIndex; i < MAX_TEXTURE_SLOTS; ++i)
        rd.textureSlots[i] = 0;
}

void resetBatchStats() {

    rd.quadCount = 0;
    rd.renderCount = 0;
}

void beginBatch() {

    rd.quadBufferPtr = rd.quadBuffer;
}

void endBatch() {

    GLsizeiptr size = (uint8_t*) rd.quadBufferPtr - (uint8_t*) rd.quadBuffer;
    glBindBuffer(GL_ARRAY_BUFFER, rd.vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, rd.quadBuffer);
}

void renderBatch() {
    
    // Bind all the textures
    for (uint32_t i = 0; i < rd.textureIndex; ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, rd.textureSlots[i]);
    }

    // Draw the current batch
    glBindVertexArray(rd.vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rd.ebo);
    glDrawElements(GL_TRIANGLES, (int)rd.indexCount, GL_UNSIGNED_INT, nullptr);
    rd.renderCount++;

    // Reset the index count and texture index
    rd.indexCount = 0;
    rd.textureIndex = 1;

    // Unbind all the textures
    for (uint32_t i = 0; i < rd.textureIndex; ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void terminateRenderer() {

    glDeleteVertexArrays(1, &rd.vao);
    glDeleteBuffers(1, &rd.vbo);
    glDeleteBuffers(1, &rd.ebo);

    glDeleteTextures(1, &rd.defaultTexture->textureID);
    delete rd.defaultTexture;

    delete[] rd.textureSlots;
    delete[] rd.quadBuffer;
}
