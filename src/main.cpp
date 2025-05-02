// Solar System.cpp : Defines the entry point for the application.
//

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include <filesystem>
#include <string>
#include "Shader.h"
#include "Sphere/Sphere.h"

using namespace std;

float triangle[] = {
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
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST);

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

    //Test Triangle
    /*GLuint testVAO, testVBO;
    glGenVertexArrays(1, &testVAO);
    glGenBuffers(1, &testVBO);

    glBindVertexArray(testVAO);
    glBindBuffer(GL_ARRAY_BUFFER, testVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);*/


    Sphere planet(1.0f);
    // Generate transformation matrices
    //glm::mat4 model = glm::mat4(1.0f);  // Identity matrix
    //glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));  // Camera position
    //glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);  // Perspective projection

    //shader.use();
    //shader.setMat4("model", model);
    //shader.setMat4("view", view);
    //shader.setMat4("projection", projection);
    // Load OpenGL functions via GLAD
    while (!glfwWindowShouldClose(window))
    {
        //glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // dark gray instead of black
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

        shader.use();
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
        //Test Triangle
        /*glBindVertexArray(testVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        */
        planet.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
