cmake_minimum_required(VERSION 3.20)
project(sbre_template)

set(CMAKE_CXX_STANDARD 17)

# OpenGL
include_directories(/opt/homebrew/Cellar/glew/2.2.0_1/include)
include_directories(/opt/homebrew/Cellar/glfw/3.3.4/include)
link_directories(/opt/homebrew/Cellar/glew/2.2.0_1/lib)
link_directories(/opt/homebrew/Cellar/glfw/3.3.4/lib)

# External Libraries
include_directories(src/vendor)

# ImGUI folder
include_directories(src/vendor/imgui)

file(GLOB IMGUI_SOURCE_FILES src/vendor/imgui/*.cpp)
file(GLOB STB_IMAGE_SOURCE src/vendor/stb_image/*.cpp)
file(GLOB SOURCE_FILES src/*.cpp src/engine/*.cpp)

add_executable(sbre_template ${SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${STB_IMAGE_SOURCE})

# Link Libraries
find_package(OpenGL REQUIRED)
target_link_libraries(sbre_template PRIVATE OpenGL::GL)
find_package(glfw3 REQUIRED)
target_link_libraries(sbre_template PRIVATE glfw.3.3)
find_package(GLEW REQUIRED)
target_link_libraries(sbre_template PRIVATE GLEW)
