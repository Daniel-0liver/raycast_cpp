#include "Utils.hpp"

Player 	player;
Map		map;
Rays	rays;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	map.drawMap2D();
	player.drawPlayer();
	rays.drawRays3D(map, player);
	glutSwapBuffers();
}

void buttons(unsigned char key, int x, int y)
{
	if (key == 'q') { glutLeaveMainLoop(); }
	else
		player.playerMovement(key, x, y);
}

void init()
{
	glClearColor(0.3, 0.3, 0.3, 0);
	gluOrtho2D(0, 1024, 510, 0);
}

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 510);
	glutCreateWindow("RayCast - Oliver");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(buttons);
	glutMainLoop();	

	return (0);
}