/*
When creating your project, uncheck OWL,
uncheck Class Library, select Static
instead of Dynamic and change the target
model to Console from GUI.
Also link glut.lib to your project once its done.
*/
/*
Code developed by Rafael Pais Cardoso in 10/08/2018.
DRE: 116170488
*/

#define _USE_MATH_DEFINES
//Width and height of the window. If necessary, change these values.
#define WIDTH 600
#define HEIGHT 600

#include <OpenGL/gl.h>     // The GL Header File
#include <cmath>
#include <stdlib.h>
#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header
#include <iostream>
#include <vector>

using namespace std;

//Creates a class to handle OrderedPairs
class OrderedPair {

public:
	float getAxis_x(void);
	float getAxis_y(void);
	OrderedPair(float x_value, float y_value);

private:
	float x;
	float y;
};

//Sets the ordered pair
OrderedPair::OrderedPair(float x_value, float y_value) {
	x = x_value;
	y = y_value;
}

float OrderedPair::getAxis_x(void) {
	return x;
}

float OrderedPair::getAxis_y(void) {
	return y;
}


int firstClick = 0;
vector<OrderedPair> pointsArray;

void mouse(int button, int state, int x, int y) {
	/*
	If the left mouse button was pressed then the coordinates of the points will be stored inside the vector (pointsArray).
	If the size of the vector is greater than 1, then it'll start drawing the lines connecting each point after each left mouse button click.
	*/

	glColor3f(0.0, 0.0, 1.0);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (firstClick == 0) {
			pointsArray.push_back(OrderedPair((2.*x) / WIDTH - 1, -(2.*y) / HEIGHT + 1));
			firstClick++;
		}
		else {
			pointsArray.push_back(OrderedPair((2.*x) / WIDTH - 1, -(2.*y) / HEIGHT + 1));
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < (int)pointsArray.size(); i++) {
				glVertex2f(pointsArray[i].getAxis_x(), pointsArray[i].getAxis_y());
			}
			glEnd();
			glFlush();
			glutSwapBuffers();
			firstClick++;
		}
	}

	/*
	If the right mouse button was pressed and there are more than 3 points already stored inside the vector
	then the width and height for each pair of adjacent points will be calculated and this value will be divided by 4.
	This will give us 3 new points between each pair of adjacent points.
	These points will be stored inside a temporary vector (tempArray).
	After calculating all new points, they will be drawn on the window.
	*/
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && firstClick >= 3) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float dy;
		float dx;
		vector<OrderedPair> tempArray;

		tempArray.push_back(OrderedPair((pointsArray.front()).getAxis_x(), (pointsArray.front()).getAxis_y()));
		for (int i = 0; i < (int)pointsArray.size() - 1; i++) {
			dx = (pointsArray[i + 1].getAxis_x() - pointsArray[i].getAxis_x()) / 4;
			dy = (pointsArray[i + 1].getAxis_y() - pointsArray[i].getAxis_y()) / 4;
			for (int j = 1; j < 4; j++) {
				tempArray.push_back(OrderedPair((pointsArray[i].getAxis_x() + (j * dx)), (pointsArray[i].getAxis_y() + (j*dy))));
			}
		}

		tempArray.push_back(OrderedPair((pointsArray.back()).getAxis_x(), (pointsArray.back()).getAxis_y()));

		pointsArray.swap(tempArray);

		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < (int)pointsArray.size(); i++) {
			glVertex2f(pointsArray[i].getAxis_x(), pointsArray[i].getAxis_y());
		}
		glEnd();
		glFlush();
		glutSwapBuffers();

		tempArray.erase(tempArray.begin(), tempArray.end());
		vector<OrderedPair>().swap(tempArray); //Clean tempArray
	}
}

//Print the header with my name, dre and instructions
void header() {
	//Sets the position of the text in the window using the x and y coordinates
	glRasterPos2f(-1, 0.9);
	string name = "Rafael Pais Cardoso\n";
	string dre = "DRE: 116140788";
	string instruction1 = "Left mouse button -> creates points";
	string instruction2 = "Right mouse button -> smooths connected points";
	int len_name = (int)name.length();
	int len_dre = (int)dre.length();
	int len_instruction1 = (int)instruction1.length();
	int len_instruction2 = (int)instruction2.length();

	//Loops to display character by character
	for (int i = 0; i < len_name; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, name[i]);
	}

	glRasterPos2f(-1, 0.8);
	for (int i = 0; i < len_dre; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, dre[i]);
	}

	glRasterPos2f(-1, 0.7);
	for (int i = 0; i < len_instruction1; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instruction1[i]);
	}

	glRasterPos2f(-1, 0.6);
	for (int i = 0; i < len_instruction2; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instruction2[i]);
	}
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(4.0);
	header();
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Rafael Pais Cardoso");
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutMainLoop();
	return EXIT_SUCCESS;
}