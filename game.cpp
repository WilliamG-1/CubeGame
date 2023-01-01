#include "game.h"
#include <iostream>
#include <math.h>
bool gameRunning = true;
Game::Game()
    :
    window("Cube Game", 800, 600), camera(45.0f, 800.0f, 600.0f, 0.1f, 100.0f), cube(1.0f), cube2(1.0f), center(1.0f),
    Red(1.0f, 0.0f, 0.0f, 1.0f), Green(0.0f, 1.0f, 0.0f, 1.0f), Blue(0.0f, 0.0f, 1.0f, 1.0f)
{
    glEnable(GL_DEPTH_TEST);
    shader.init_shaders("shaders/lightVertex.vert", "shaders/lightFragment.frag");
}

void Game::initKeyCallbacks()
{
    glfwSetKeyCallback(window.getWindow(), [](GLFWwindow* win, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_0 && action == GLFW_PRESS)
        {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        }
        if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        {
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        }
    });
}
void Game::composeFrame()
{

    Transformations::translate3D(cube, 0, 20, 0);
    Transformations::translate3D(cube2, 0, 2, 0);
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            floor.push_back(Cube(1.0f));
            Transformations::translate3D(floor.back(), i - 5, 0, j - 5);
        }
    }
    for (int i = 0; i < 8; i++)
    {
        randomCubes.push_back(Cube(1.0f));
        int randomX = Transformations::randint(-4, 4);
        int randomY = Transformations::randint(7, 13);
        int randomZ = Transformations::randint(-4, 4);
        Transformations::translate3D(randomCubes[i], randomX, randomY, randomZ);
        std::printf("Random Transform %d: (%d, %d, %d)\n", i, randomX, randomY, randomZ);
    }
    std::printf("Camera: (%.2f, %.2f, %.2f)", camera.get_position().x, camera.get_position().y, camera.get_position().z);
}

void Game::run()
{
    composeFrame();
    while (!glfwWindowShouldClose(window.getWindow()))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        processInput();

        shader.setUniformMat4f("u_ViewProjection", camera.get_projection_view_matrix());

        for (Cube& c : floor)
        {
            renderer.draw3D(shader, c, Color(0.7f, 0.8f, 0.8f, 1.0f));
        }
        
        if (cube.get_position_vector().y >= 1){
            cube.applyGravity(deltaTime.getDT());
            
        }
        std::printf("Cube      Position: %.2f, %.2f, %.2f\n", cube.get_position_vector().x, cube.get_position_vector().y, cube.get_position_vector().z);
        std::printf("Collision Position: %.2f, %.2f, %.2f\n", cube.get_collision_box().center.x, cube.get_collision_box().center.y, cube.get_collision_box().center.z);
        std::printf("-------------------------------------\n");
        if (Collisions::aabb_is_colliding(cube.get_collision_box(), cube2.get_collision_box())) 
        {
            Collisions::resolve_aabb_y_collisions(cube.get_collision_box(), cube2.get_collision_box(), cube, cube.get_velocity().y);
            cube.cancel_y_velocity();
        }
        renderer.draw3D(shader, cube, Color(1.0f, 1.0f, 1.0f, 1.0f));
        renderer.draw3D(shader, cube2, Red);
        
        //std::printf("Camera Position: {%.2f, %.2f, %.2f}\n", camera.get_position().x, camera.get_position().y, camera.get_position().z);
        deltaTime.updateDT();
       // deltaTime.printFPS();
        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }
    glfwTerminate();
}


void Game::processInput()
{
    // Camera Movement
    if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        camera.move(CameraDirection::LEFT, deltaTime.getDT());
    if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        camera.move(CameraDirection::RIGHT, deltaTime.getDT());
    if (glfwGetKey(window.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        camera.move(CameraDirection::FORWARD, deltaTime.getDT());
    if (glfwGetKey(window.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        camera.move(CameraDirection::BACKWARD, deltaTime.getDT());   
    if (glfwGetKey(window.getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.move(CameraDirection::UP, deltaTime.getDT());
    if (glfwGetKey(window.getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.move(CameraDirection::DOWN, deltaTime.getDT());

    if (glfwGetKey(window.getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        camera.panCamera(0, -1, deltaTime.getDT());
    }
    if (glfwGetKey(window.getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        camera.panCamera(0, 1, deltaTime.getDT());
    }
    if (glfwGetKey(window.getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
    {
        camera.panCamera(1, 0, deltaTime.getDT());
    }
    if (glfwGetKey(window.getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        camera.panCamera(-1, 0, deltaTime.getDT());
    }
    if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.getWindow(), true);

}
