// Solar System.cpp : Defines the entry point for the application.
//

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include <filesystem>
#include <string>
#include "Shader.h"

using namespace std;

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

void frameBuffer_size_callback(GLFWwindow* window,int height,int width){
	glViewport(0, 0, width, height);
}

std::string getFullPath(const std::string& relativePath) {
    std::filesystem::path cwd = std::filesystem::current_path();
    return (cwd / relativePath).string();
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
    int window_width = 1280;
    int window_height = 720;
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Solar System", nullptr, nullptr);
   

    if (!window) {
        const char* description;
        int code = glfwGetError(&description);
        std::cerr << "Failed to create GLFW window\n";
        std::cout << code <<" " << description << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frameBuffer_size_callback);

    //  Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    //Compile and Setup shader
    std::string fullVertexPath = getFullPath("assets/shaders/basic.vs");
    std::string fullFragmentPath = getFullPath("assets/shaders/basic.fs");
    cout << fullVertexPath << endl;
    cout << fullFragmentPath << endl;
    Shader shader("assets/shaders/basic.vs", "assets/shaders/basic.fs");

    // Generate and bind VAO, VBO for the triangle
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Load OpenGL functions via GLAD
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
