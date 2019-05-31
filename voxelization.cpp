// voxelization.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <glm/glm.hpp>

#include "CubeDraw.h"
#include "TrackBall.h"
#include "MeshLoader.h"

const int width = 800;
const int height = 800;

using namespace std;

int main()
{
	//glm::vec3 cubePos(0.f, 0.f, 0.f);
	std::vector<glm::vec3> cubePositions({ 
		glm::vec3(-10.f, 0.f, 0.f),
		glm::vec3(-8.f, 0.f, 0.f)});
	
	TrackBall trackBall(400.f, 400.f, 100.f);
	CubeDraw cubeDraw(trackBall);
	//cubeDraw.setScale(0.5);
	MeshLoader meshLoader;

	// load mesh
	meshLoader.parseObj("../models/sphere.obj");
	// create the window
	sf::Window window(sf::VideoMode(width, height), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);

	// activate the window
	window.setActive(true);

	// run the main loop
	bool running = true;

	// mouse is down
	bool mouseDown = false;

	// mouse position
	float mouse_x = -1, mouse_y = -1;

	while (running)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				running = false;
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				//glViewport(0, 0, event.size.width, event.size.height);
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				mouseDown = true;
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				mouseDown = false;
				mouse_x = -1;
				mouse_y = -1;
			}
			else if (mouseDown && event.type == sf::Event::MouseMoved) {
				float cur_mouse_x = event.mouseMove.x;
				float cur_mouse_y = event.mouseMove.y;
				cout << "cur_mouse_x: " << cur_mouse_x << endl;
				// only rotate when the last mouse position is known
				if (mouse_x != -1) {
					trackBall.rotate(mouse_x, mouse_y, cur_mouse_x, cur_mouse_y);
				}
				// update mouse position
				mouse_x = cur_mouse_x;
				mouse_y = cur_mouse_y;
			}
		}
		
		trackBall.setView();
		cubeDraw.drawCubes(cubePositions);
		window.display();
	}


	return 0;
}