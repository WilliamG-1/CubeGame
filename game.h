#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "window.h"
#include "camera.h"
#include "shader.h"
#include "renderer.h"
#include "texture.h"
#include "cube.h"
#include "transformations.h"
#include "shape3D.h"
class Game 
{
public:
    Game();
    void run();

private:
    Window window;
    Shader shader;
    Renderer renderer;
    PerspectiveCamera camera;
    Cube cube;
    Cube cube2;
    DeltaTime deltaTime;
    std::vector<Cube> floor;
    
    float dt = 0;
    
    void composeFrame();
    void processInput();
    void initKeyCallbacks();
    void updateDT();
};