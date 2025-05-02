#pragma once
#include<vector>
#include<glad/glad.h>
#include<glm/glm.hpp>

class Sphere {
public:
    Sphere(float radius, unsigned int sectors = 36, unsigned int stacks = 18);
	~Sphere();

	void draw();
private:
    float radius;
    unsigned int sectors, stacks;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    GLuint VAO, VBO, EBO;

    void generateMesh();
    void setupMesh();
};