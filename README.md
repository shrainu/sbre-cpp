# SBRE - Simple Batch Rendering Engine
 
SBRE is an OpenGL bathch rendering framework, because its mainly focused around batch rendering,
you can't render images or shapes in seperate draw calls for now. Currently it is capable of rendering
100K+ sprites in single frame with 70 FPS on my machine which doesn't even have a dedicated GPU. There 
is no native UI or Text Rendering available for now, but it uses ImGUI so you can still achive some
kind of UI using ImGUI.

SBRE lets you use your own shaders for rendering images. Make sure to take a look at the base shaders of
SBRE before writing/using your own shaders.

> Current version 0.1c

## How to use

If you are using MacOS this Github repo pretty much has everything you need in order to use this framework.
Otherwise you will need to include GLEW and GLFW3 to your project. All the other dependencies are compiled 
with the engine so there is no need to include them.

> A detailed Documentation will be available in the future
