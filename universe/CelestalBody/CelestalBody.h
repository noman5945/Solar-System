#pragma once
#include<glm/glm.hpp>

class CelestalBody
{
public:
	CelestalBody(float radius,glm::vec3 position);
	virtual ~CelestalBody();
	virtual void update(float deltaTime);
	virtual void draw();
	
protected:
	float radius;
	glm::vec3 position;
	glm::vec3 color;
};

