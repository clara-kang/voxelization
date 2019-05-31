#pragma once
#include <vector>
#include "TrackBall.h"
#include <glm/glm.hpp>

class CubeDraw {
public:
	CubeDraw(TrackBall &trackBall);
	CubeDraw(TrackBall &trackBall, float x, float y, float z);
	void setPos(float x, float y, float z);
	void setScale(float scale);
	void drawCubes(std::vector<glm::vec3> &positions);
private:
	TrackBall &trackBall;
	glm::vec3 pos;
	float scale;
	void setup();
	void setPerspective();
	void drawCube(glm::vec3 &offset);
};