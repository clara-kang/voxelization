#pragma once
#include <glm/glm.hpp>

class TrackBall {
public:
	TrackBall();
	TrackBall(float x, float y, float R);
	void rotate(float s_x, float s_y, float e_x, float e_y);
	void setView();
private:
	glm::mat4 trans_matrix;
	glm::mat4 rot_matrix;
	float pos_x, pos_y;
	float pos_z;
	float R;
	void setup();
};
