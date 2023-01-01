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
#include "collisions.h"

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
    Cube center;
    DeltaTime deltaTime;
    std::vector<Cube> floor;
    std::vector<Cube> randomCubes;
    float dt = 0;
    
    void composeFrame();
    void processInput();
    void initKeyCallbacks();
    void updateDT();

    // Colors lol
    Color Red;
    Color Green;
    Color Blue;
};