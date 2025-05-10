#pragma once
#include<vector>
#include<glad/glad.h>
#include<glm/glm.hpp>

class Sphere {
public:
    Sphere(float radius, unsigned int sectors = 36, unsigned int stacks = 18,bool smooth=true,int up=3);
	~Sphere();
    //Getters and Setters
    float getRadius() const { return radius; }
    unsigned int getSectors() const { return sectors; }
    unsigned int getStacks() const { return stacks; }
    bool getSmooth() const { return smooth; }
    int getUpAxis() const { return upAxis; }
    void set(float radius, unsigned int sectors = 36, unsigned int stacks = 18, bool smooth = true, int up = 3);
    void setRadius(float radius);
    void setSectorCount(unsigned int sectorCount);
    void setStackCount(unsigned int stackCount);
    void setSmooth(bool smooth);
    void setUpAxis(int up);
    void reverseNormals();

    // for vertex data
    unsigned int getVertexCount() const { return (unsigned int)vertices.size() / 3; }
    unsigned int getNormalCount() const { return (unsigned int)normals.size() / 3; }
    unsigned int getTexCoordCount() const { return (unsigned int)texCoords.size() / 2; }
    unsigned int getIndexCount() const { return (unsigned int)indices.size(); }
    unsigned int getLineIndexCount() const { return (unsigned int)lineIndices.size(); }
    unsigned int getTriangleCount() const { return getIndexCount() / 3; }
    unsigned int getVertexSize() const { return (unsigned int)vertices.size() * sizeof(float); }
    unsigned int getNormalSize() const { return (unsigned int)normals.size() * sizeof(float); }
    unsigned int getTexCoordSize() const { return (unsigned int)texCoords.size() * sizeof(float); }
    unsigned int getIndexSize() const { return (unsigned int)indices.size() * sizeof(unsigned int); }
    unsigned int getLineIndexSize() const { return (unsigned int)lineIndices.size() * sizeof(unsigned int); }
    const float* getVertices() const { return vertices.data(); }
    const float* getNormals() const { return normals.data(); }
    const float* getTexCoords() const { return texCoords.data(); }
    const unsigned int* getIndices() const { return indices.data(); }
    const unsigned int* getLineIndices() const { return lineIndices.data(); }

	void draw();
    void draw_v_2();
private:
    float radius;
    unsigned int sectors, stacks;
    bool smooth;
    int upAxis;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> normals;
    std::vector<float> texCoords;
    std::vector<unsigned int> lineIndices;
    // interleaved
    std::vector<float> interleavedVertices;
    int interleavedStride;                  // # of bytes to hop to the next vertex (should be 32 bytes)

    GLuint VAO, VBO, EBO;

    void clearMemory();
    void addVertex(float x,float y,float z);
    void addNormal(float nx, float ny, float nz);
    void addTexCoord(float s,float t);
    void addIndices(unsigned int l1, unsigned int l2, unsigned int l3);
    void buildInterleavedVertices();
    void changeUpAxis(int from,int to);
    void generateMesh();
    void setupMesh();
};