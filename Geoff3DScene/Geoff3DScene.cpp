//Geoffrey Atkinson
//C00184861
//24/04/2017

#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/Graphics/Shader.hpp"
#include "SFML/OpenGL.hpp" 
#include <iostream> 

#include "Camera.h"

using namespace std;

void calcNormalVector(GLfloat pt1[3], GLfloat pt2[3], GLfloat pt3[3], GLfloat n[3]) {

	GLfloat v1[3], v2[3]; 
	for (int i = 0;i<3;i++) {
		v1[i] = pt2[i] - pt1[i];
		v2[i] = pt3[i] - pt2[i];
	}
	n[0] = v1[1] * v2[2] - v2[1] * v1[2];
	n[1] = v1[2] * v2[0] - v2[2] * v1[0];
	n[2] = v1[0] * v2[1] - v2[0] * v1[1];

}


void drawFloor() {
	GLfloat normal[3];
	float fValOne = -100.0f, fValTwo = -96.0f;
	GLfloat floorPoints[][3] = { { fValOne,0.0f,fValTwo },
	{ fValOne,0.0f,fValOne },	
	{ fValTwo,0.0f,fValTwo },	
	{ fValTwo,0.0f,fValOne } };
	int increasebyThis = 4;
	sf::Texture texLidwa;
	sf::Texture texLidrw;
	if (!texLidwa.loadFromFile("imgs/rosewood.jpg")) {}
	if (!texLidrw.loadFromFile("imgs/wood_ash.jpg")) {}
	glEnable(GL_TEXTURE_2D);
	for (int c1 = 0; c1 <= 49; c1 += 1) {
		for (int c = 0; c <= 24; c += 1) {
			int sequence[2] = { 1,2 };
			if (c1 % 2 == 0) {
				sequence[0] = 1;
				sequence[1] = 2;
			}
			else {
				sequence[0] = 2;
				sequence[1] = 1;
			}
			int i = 0;
			for (i = 0; i <= 1; i++) {
				switch (sequence[i]) {
				case 1: {
					sf::Texture::bind(&texLidwa);
					glBegin(GL_QUADS);
					calcNormalVector(floorPoints[2], floorPoints[3], floorPoints[0], normal);
					glNormal3fv(normal);
					glTexCoord2f(0, 0);		glVertex3fv(floorPoints[0]);
					glTexCoord2f(0, 1);		glVertex3fv(floorPoints[1]);
					glTexCoord2f(1, 1);		glVertex3fv(floorPoints[3]);
					glTexCoord2f(1, 0);		glVertex3fv(floorPoints[2]);
					glEnd();
					break;
				}
				case 2: {
					sf::Texture::bind(&texLidrw);
					glBegin(GL_QUADS);
					calcNormalVector(floorPoints[2], floorPoints[3], floorPoints[0], normal);
					glNormal3fv(normal);
					glTexCoord2f(0, 0);		glVertex3fv(floorPoints[0]);
					glTexCoord2f(0, 1);		glVertex3fv(floorPoints[1]);
					glTexCoord2f(1, 1);		glVertex3fv(floorPoints[3]);
					glTexCoord2f(1, 0);		glVertex3fv(floorPoints[2]);
					glEnd();
					break;
				}
				}
				floorPoints[0][0] = floorPoints[0][0] + increasebyThis;
				floorPoints[1][0] = floorPoints[1][0] + increasebyThis;
				floorPoints[2][0] = floorPoints[2][0] + increasebyThis;
				floorPoints[3][0] = floorPoints[3][0] + increasebyThis;
			}
		}
		floorPoints[0][0] = fValOne;
		floorPoints[0][2] = floorPoints[0][2] + increasebyThis;
		floorPoints[1][0] = fValOne;
		floorPoints[1][2] = floorPoints[1][2] + increasebyThis;
		floorPoints[2][0] = fValTwo;
		floorPoints[2][2] = floorPoints[2][2] + increasebyThis;
		floorPoints[3][0] = fValTwo;
		floorPoints[3][2] = floorPoints[3][2] + increasebyThis;
	}
}


int main()
{
	int width = 600, height = 600;
	sf::RenderWindow App(sf::VideoMode(width, height, 32), "SFML OpenGL");
	aiVector3D position(0, 6, 13);
	Camera camera;
	camera.Init(position); 
	glClearDepth(1.f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
	glMatrixMode(GL_PROJECTION);
	gluPerspective(90.f, (float)width / height, 1.f, 50.0f);

	while (App.isOpen())
	{
		sf::Event Event;
		while (App.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
				App.close();

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				App.close();

			camera.Update(Event);
		}

		//Prepare for drawing 
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW); 
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glLoadIdentity();
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHTING);
		camera.ViewingTransform();
		GLfloat normal[3];

		drawFloor();

		GLfloat rgbvals2[] = {3.0f, 3.0f, 3.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, rgbvals2);

		App.display();
	}
	return EXIT_SUCCESS;
}