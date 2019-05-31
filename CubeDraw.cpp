#include "pch.h"
#include "CubeDraw.h"
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

CubeDraw::CubeDraw(TrackBall &trackBall) :
	pos(0.f, 0.f, 0.f),
	scale(1.f),
	trackBall(trackBall){

}

CubeDraw::CubeDraw(TrackBall &trackBall, float x, float y, float z) :
	pos(x, y, z),
	scale(1.f),
	trackBall(trackBall) {
}

void CubeDraw::setPos(float x, float y, float z) {
	this->pos = glm::vec3(x, y, z);
}

void CubeDraw::setScale(float scale) {
	this->scale = scale;
}

void CubeDraw::setPerspective() {
	//// Setup a perspective projection & Camera position
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glm::mat4 perspective_mtx = glm::perspective(75.f, 1.f, 1.f, 300.f);
	glLoadMatrixf(glm::value_ptr(perspective_mtx));
}

void CubeDraw::setup() {
	glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(glm::vec4(0.1f, 0.1f, 0.1f, 1.f)));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(glm::vec4(1.f, 1.f, 1.f, 1.f)));
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(glm::vec4(1.f, 1.f, 1.f, 1.f)));
	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(glm::vec4(5.f, 10.f, 0.f, 1.f)));
	//glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.f);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.f);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.f);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthMask(GL_TRUE);
}

void CubeDraw::drawCube(glm::vec3 &offset) {
	// individual transform

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(-offset.x, -offset.y, -offset.z);

	//glm::mat4 trans_mtx = glm::translate(glm::mat4(1.f), glm::vec3(offset.x, offset.y, offset.z));
	//glMultMatrixf(glm::value_ptr(trans_mtx));
	//glLoadIdentity();

	glBegin(GL_QUADS);//draw some squares
	glColor3f(1.f, 1.f, 1.f);
	glVertex3f(-1.f, -1.f, -1.f);
	glVertex3f(-1.f, 1.f, -1.f);
	glVertex3f(1.f, 1.f, -1.f);
	glVertex3f(1.f, -1.f, -1.f);

	glVertex3f(-1.f, -1.f, 1.f);
	glVertex3f(-1.f, 1.f, 1.f);
	glVertex3f(1.f, 1.f, 1.f);
	glVertex3f(1.f, -1.f, 1.f);

	glVertex3f(-1.f, -1.f, -1.f);
	glVertex3f(-1.f, 1.f, -1.f);
	glVertex3f(-1.f, 1.f, 1.f);
	glVertex3f(-1.f, -1.f, 1.f);

	glVertex3f(1.f, -1.f, -1.f);
	glVertex3f(1.f, 1.f, -1.f);
	glVertex3f(1.f, 1.f, 1.f);
	glVertex3f(1.f, -1.f, 1.f);

	glVertex3f(-1.f, -1.f, 1.f);
	glVertex3f(-1.f, -1.f, -1.f);
	glVertex3f(1.f, -1.f, -1.f);
	glVertex3f(1.f, -1.f, 1.f);

	glVertex3f(-1.f, 1.f, 1.f);
	glVertex3f(-1.f, 1.f, -1.f);
	glVertex3f(1.f, 1.f, -1.f);
	glVertex3f(1.f, 1.f, 1.f);

	glEnd();
	glPopMatrix();
}

void CubeDraw::drawCubes(std::vector<glm::vec3> &positions) {
	setup();
	setPerspective();
	
	//glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	//glTranslatef(-pos.x, -pos.y, -pos.z);
	glScalef(scale, scale, scale);
	for (int i = 0; i < positions.size(); i++) {
		drawCube(positions[i]);
	}
}