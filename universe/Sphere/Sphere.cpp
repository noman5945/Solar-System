#include"Sphere.h"
#include<cmath>
#include<glm/gtc/constants.hpp>
#include <iostream>
using namespace std;

Sphere::Sphere(float radius, unsigned int sectors, unsigned int stacks)
	: radius(radius), sectors(sectors), stacks(stacks) {
	generateMesh();
	setupMesh();
}


Sphere::~Sphere(){
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
/*
Create Mesh of Vertices for the UV Sphere
*/
void Sphere::generateMesh(){
	vertices.clear();
	indices.clear();
	//From North Pole to South Pole
	for (unsigned int i = 0;i <= stacks;++i) {
		float stackAngle = glm::pi<float>() / 2 - i * glm::pi<float>();
		float xy = radius * cosf(stackAngle);
		float z = radius * sinf(stackAngle);
		//Around the equetor
		for (unsigned int j = 0;j <= sectors;++j) {
			float sectorAngle = j * 2 * glm::pi<float>() / sectors;

			float x = xy * cosf(sectorAngle);
			float y = xy * sinf(sectorAngle);

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		}
	}
	//Triangles Genarate
	for (unsigned int i = 0; i < stacks; ++i) {
		for (unsigned int j = 0; j < sectors; ++j) {
			int first = (i * (sectors + 1)) + j;
			int second = first + sectors + 1;

			indices.push_back(first);
			indices.push_back(second);
			indices.push_back(first + 1);

			indices.push_back(second);
			indices.push_back(second + 1);
			indices.push_back(first + 1);
		}
	}
	std::cout << "Vertices count: " << vertices.size() << std::endl;
	std::cout << "Indices count: " << indices.size() << std::endl;
}

void Sphere::setupMesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Sphere::draw() {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}