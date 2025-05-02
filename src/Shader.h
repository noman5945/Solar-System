#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp> 
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    GLuint ID;

    // Constructor: Builds and compiles the shader program from the given vertex and fragment shader paths
    Shader(const char* vertexPath, const char* fragmentPath);

    // Use the current shader program
    void use();
    void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
    
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
