#include "pch.h"
#include "TrackBall.h"
#include <iostream>
#include <SFML/OpenGL.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

using namespace std;

TrackBall::TrackBall() {
	setup();
}

TrackBall::TrackBall(float x, float y, float R) :
	pos_x(x),
	pos_y(y),
	R(R),
	rot_matrix(glm::mat4(1.0f)),
	trans_matrix(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 10.f, -100.f))) {
}

void TrackBall::setup() {
}

void TrackBall::setView() {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(this->trans_matrix));
	glMultMatrixf(glm::value_ptr(this->rot_matrix));
}

void TrackBall::rotate(float s_x, float s_y, float e_x, float e_y) {
	float rel_sx = s_x - pos_x;
	float rel_sy = s_y - pos_y;
	float rel_ex = e_x - pos_x;
	float rel_ey = e_y - pos_y;
	// check if mouse positions in disk
	if (rel_sy * rel_sy + rel_sx * rel_sx >= R * R ||
		rel_ex * rel_ex + rel_ey * rel_ey >= R * R) {
		return;
	}
	float rel_sz = sqrt(R*R - rel_sx * rel_sx - rel_sy * rel_sy);
	float rel_ez = sqrt(R*R - rel_ex * rel_ex - rel_ey * rel_ey);
	glm::vec3 o2start(rel_sx, rel_sy, rel_sz);
	glm::vec3 o2end(rel_ex, rel_ey, rel_ez);
	o2start = glm::normalize(o2start);
	o2end = glm::normalize(o2end);

	cout << "o2start: " << o2start.x << ", " << o2start.y << ", " << o2start.z << endl;
	cout << "o2end: " << o2end.x << ", " << o2end.y << ", " << o2end.z << endl;

	glm::vec3 rot_axis = glm::normalize(glm::cross(o2start, o2end));
	float rot_angle = acos(glm::dot(o2start, o2end));
	std::cout << "rot_angle: " << rot_angle << std::endl;
	this->rot_matrix = glm::rotate(glm::mat4(1.f), rot_angle, -rot_axis) * this->rot_matrix;
	//this->rot_matrix = glm::rotate(this->rot_matrix, 0.1f, glm::vec3(0.f, 1.f, 0.f));


}