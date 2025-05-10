#include"Sphere.h"
#include<cmath>
#include<glm/gtc/constants.hpp>
#include <iostream>
using namespace std;

const int MIN_SECTOR_COUNT = 2;
const int MIN_STACK_COUNT = 2;

Sphere::Sphere(float radius, unsigned int sectors, unsigned int stacks,bool smooth,int up)
	: radius(radius), sectors(sectors), stacks(stacks),smooth(smooth),upAxis(up) {
	generateMesh();
	setupMesh();
}


Sphere::~Sphere(){
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

//Setters
void Sphere::setRadius(float radius){
	this->radius = radius;
}

void Sphere::setUpAxis(int up){
	this->upAxis = up;
}

void Sphere::setSectorCount(unsigned int sector) {
	this->sectors = sector;
}

void Sphere::setStackCount(unsigned int stack) {
	this->stacks = stack;
}

void Sphere::setSmooth(bool smooth){
	this->smooth = smooth;
}

/*
Reverse the Normals
Flip the face normals to opposite directions
*/
void Sphere::reverseNormals() {
	std::size_t i, j;
	std::size_t count = normals.size();
	for (i = 0, j = 3;i < count;i += 3, j += 8) {
		normals[i] *= -1;
		normals[i+1] *= -1;
		normals[i+2] *= -1;

		interleavedVertices[j] = normals[i];
		interleavedVertices[j + 1] = normals[i + 1];
		interleavedVertices[j + 2] = normals[i + 2];

	}
	// also reverse triangle windings
	unsigned int tmp;
	count = indices.size();
	for (i = 0;i < count;i += 3) {
		tmp = indices[i];
		indices[i] = indices[i+2];
		indices[i + 2] = tmp;
	}

}

void Sphere::clearMemory() {
	std::vector<float>().swap(vertices);
	std::vector<float>().swap(normals);
	std::vector<float>().swap(texCoords);
	std::vector<float>().swap(interleavedVertices);
	std::vector<unsigned int>().swap(indices);
	std::vector<unsigned int>().swap(lineIndices);
}

void Sphere::addVertex(float x, float y, float z) {
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
}

void Sphere::addNormal(float x, float y, float z) {
	normals.push_back(x);
	normals.push_back(y);
	normals.push_back(z);
}

void Sphere::addTexCoord(float s,float t) {
	texCoords.push_back(s);
	texCoords.push_back(t);
}

void Sphere::addIndices(unsigned int l1, unsigned int l2, unsigned int l3) {
	indices.push_back(l1);
	indices.push_back(l2);
	indices.push_back(l3);
}

/*
generate interleaved vertices: V/N/T
stride must be 32 bytes
*/
void Sphere::buildInterleavedVertices() {
	std::vector<float>().swap(interleavedVertices);

	std::size_t i, j;
	std::size_t count = vertices.size();
	for (i = 0, j = 0; i < count; i += 3, j += 2)
	{
		interleavedVertices.push_back(vertices[i]);
		interleavedVertices.push_back(vertices[i + 1]);
		interleavedVertices.push_back(vertices[i + 2]);

		interleavedVertices.push_back(normals[i]);
		interleavedVertices.push_back(normals[i + 1]);
		interleavedVertices.push_back(normals[i + 2]);

		interleavedVertices.push_back(texCoords[j]);
		interleavedVertices.push_back(texCoords[j + 1]);
	}
}


///////////////////////////////////////////////////////////////////////////////
// transform vertex/normal (x,y,z) coords
// assume from/to values are validated: 1~3 and from != to
///////////////////////////////////////////////////////////////////////////////
void Sphere::changeUpAxis(int from,int to) {
	// initial transform matrix cols
	float tx[] = { 1.0f, 0.0f, 0.0f };    // x-axis (left)
	float ty[] = { 0.0f, 1.0f, 0.0f };    // y-axis (up)
	float tz[] = { 0.0f, 0.0f, 1.0f };    // z-axis (forward)

	// X -> Y
	if (from == 1 && to == 2)
	{
		tx[0] = 0.0f; tx[1] = 1.0f;
		ty[0] = -1.0f; ty[1] = 0.0f;
	}
	// X -> Z
	else if (from == 1 && to == 3)
	{
		tx[0] = 0.0f; tx[2] = 1.0f;
		tz[0] = -1.0f; tz[2] = 0.0f;
	}
	// Y -> X
	else if (from == 2 && to == 1)
	{
		tx[0] = 0.0f; tx[1] = -1.0f;
		ty[0] = 1.0f; ty[1] = 0.0f;
	}
	// Y -> Z
	else if (from == 2 && to == 3)
	{
		ty[1] = 0.0f; ty[2] = 1.0f;
		tz[1] = -1.0f; tz[2] = 0.0f;
	}
	//  Z -> X
	else if (from == 3 && to == 1)
	{
		tx[0] = 0.0f; tx[2] = -1.0f;
		tz[0] = 1.0f; tz[2] = 0.0f;
	}
	// Z -> Y
	else
	{
		ty[1] = 0.0f; ty[2] = -1.0f;
		tz[1] = 1.0f; tz[2] = 0.0f;
	}

	std::size_t i, j;
	std::size_t count = vertices.size();
	float vx, vy, vz;
	float nx, ny, nz;
	for (i = 0, j = 0; i < count; i += 3, j += 8)
	{
		// transform vertices
		vx = vertices[i];
		vy = vertices[i + 1];
		vz = vertices[i + 2];
		vertices[i] = tx[0] * vx + ty[0] * vy + tz[0] * vz;   // x
		vertices[i + 1] = tx[1] * vx + ty[1] * vy + tz[1] * vz;   // y
		vertices[i + 2] = tx[2] * vx + ty[2] * vy + tz[2] * vz;   // z

		// transform normals
		nx = normals[i];
		ny = normals[i + 1];
		nz = normals[i + 2];
		normals[i] = tx[0] * nx + ty[0] * ny + tz[0] * nz;   // nx
		normals[i + 1] = tx[1] * nx + ty[1] * ny + tz[1] * nz;   // ny
		normals[i + 2] = tx[2] * nx + ty[2] * ny + tz[2] * nz;   // nz

		// trnasform interleaved array
		interleavedVertices[j] = vertices[i];
		interleavedVertices[j + 1] = vertices[i + 1];
		interleavedVertices[j + 2] = vertices[i + 2];
		interleavedVertices[j + 3] = normals[i];
		interleavedVertices[j + 4] = normals[i + 1];
		interleavedVertices[j + 5] = normals[i + 2];
	}
}

/*
Create Mesh of Vertices for the UV Sphere

 build vertices of sphere with smooth shading using parametric equation
 x = r * cos(u) * cos(v)
 y = r * cos(u) * sin(v)
 z = r * sin(u)
 where u: stack(latitude) angle (-90 <= u <= 90)
       v: sector(longitude) angle (0 <= v <= 360)

*/
void Sphere::generateMesh(){
	// clear memory of prev arrays
	clearMemory();
	const float PI = acos(-1.0f);

	float x, y, z, xy;                           // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius; // normals
	float s, t;                                  // texCoord

	float sectorStep = 2 * PI / sectors;
	float stackStep =  PI / stacks;
	float stackAngle, sectorAngle;

	//From North Pole to South Pole
	for (unsigned int i = 0;i <= stacks;++i) {
		
		/*float stackAngle = glm::pi<float>() / 2 - i * glm::pi<float>();
		float xy = radius * cosf(stackAngle);
		float z = radius * sinf(stackAngle);*/

		stackAngle = PI / 2 - i * stackStep; //starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);      //r*cos(u)
		z = radius * sinf(stackAngle);       //r*sin(u)  

		//Around the equetor
		for (unsigned int j = 0;j <= sectors;++j) {
			/*float sectorAngle = j * 2 * glm::pi<float>() / sectors;

			float x = xy * cosf(sectorAngle);
			float y = xy * sinf(sectorAngle);

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);*/

			sectorAngle = j * sectorStep; // starting from 0 to 2pi

			//vertex position
			x = xy * cosf(sectorAngle); // r*cos(u)*cos(v)
			y = xy * sinf(sectorAngle); // r*cos(u)*sin(v)
			addVertex(x, y, z);

			// normal position
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			addNormal(nx, ny, nz);

			// vertex tex coord
			s = (float)j / sectors;
			t = (float)i / stacks;
			addTexCoord(s, t);
		}
	}
	//Triangles Genarate
	// indices
	//  k1--k1+1
	//  |  / |
	//  | /  |
	//  k2--k2+1
	unsigned int k1, k2;
	for (unsigned int i = 0; i < stacks; ++i) {
		k1 = i * (sectors + 1); // beginning of current stack
		k2 = k1 + sectors + 1;  // beginning of next stack

		for (unsigned int j = 0; j < sectors; ++j, ++k1, ++k2) {
			
			if (i!=0) {
				addIndices(k1, k2, k1 + 1); //k1---k2---k1+1
			}
			if (i != (stacks - 1)) {
				addIndices(k1 + 1, k2, k2 + 1); //k1+1---k2---k2+1
			}
			// vertical lines for all stacks
			lineIndices.push_back(k1);
			lineIndices.push_back(k2);
			// horizontal lines except 1st stack
			if (i != 0) { 
				lineIndices.push_back(k1);
				lineIndices.push_back(k1 + 1);
			}
		}
	}
	// generate interleaved vertex array as well
	buildInterleavedVertices();

	// change up axis from Z-axis to the given
	if (this->upAxis != 3)
		changeUpAxis(3, this->upAxis);

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

void Sphere::draw_v_2() {
	// interleaved array
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, interleavedStride, &interleavedVertices[0]);
	glNormalPointer(GL_FLOAT, interleavedStride, &interleavedVertices[3]);
	glTexCoordPointer(2, GL_FLOAT, interleavedStride, &interleavedVertices[6]);

	glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, indices.data());

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}