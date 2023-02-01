#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fmt/format.h>

#include "game.hpp"

Game game(800, 600);

void keyPressCallBack(GLFWwindow *window, int key, int scancode, int action, int mode);

int main(int, char **)
{
    std::cout << "Starting game" << std::endl;
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, keyPressCallBack);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height)
                                   { glViewport(0, 0, width, height); });

    game.Init();
    float current_time = 0;
    float previous_time = 0;
    float delta_time = 0;
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        current_time = glfwGetTime();
        delta_time = current_time - previous_time;
        previous_time = current_time;
        game.Update(delta_time);
        game.ProcessInput(delta_time);
        glClearColor(1.0f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.Render(delta_time);
        glfwSwapBuffers(window);
    }
    glViewport(0, 0, 800, 600);
}

void keyPressCallBack(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key >= 0 && key <= 1024)
    {
        if (action == GLFW_PRESS)
        {
            game.Keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            game.Keys[key] = false;
        }
    }
}
