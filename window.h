#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
class DeltaTime
{
public:
   void updateDT()
   {
        last = current;
        current = glfwGetTime();
        dt = current - last;
   }
   const float& getDT() const {return dt;}
   const void printDeltaTime() { std::printf("Delta Time: %.2f\n", dt);}
   const void printFPS() { std::printf("FPS: %.1f\n", 1/dt);}

private:
    float last = 0;
    float current = 0;
    float dt = 0;
};

class Window
{
public:
    Window(const char* title, int width, int height)
    {
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (window == nullptr)
        {
            std::cout << "Error, could not create a window!" << std::endl;
            glfwTerminate();

        }
        
        glfwMakeContextCurrent(window);
        // Set FramBuffer Callback (to resize window and viewport)
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        });

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
    }
    GLFWwindow* getWindow() { return window; }

private:
    GLFWwindow* window;
};