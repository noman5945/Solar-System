// Solar System.cpp : Defines the entry point for the application.
//

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include "Solar System.h"

using namespace std;

void frameBuffer_size_callback(GLFWwindow* window,int height,int width){
	glViewport(0, 0, width, height);
}

int main()
{
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Solar System", nullptr, nullptr);
    const char* description;
    int code = glfwGetError(&description);

    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        std::cout << code <<" " << description << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frameBuffer_size_callback);

    // Load OpenGL functions via GLAD
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
