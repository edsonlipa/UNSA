// #include <Windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include "node.h"
#include "rangue_t.h"


using namespace std;
const int n = 100000;
int x[n], y[n];
float xo = 0, yo = 0, xf = 0, yf = 0;
bool selection = true;

int rand_nums(){
	int x = 1 + rand() % (1001 - 1);
	return x;
}


struct Points
{
	float x, y;
	Points() { x = 0.0; y = 0.0; }
	Points(float _x, float _y) : x(_x), y(_y) {}
};


class Square
{
public:
	Points pts[4];
	Square();

	void draw(Square *sqr);
	Points mouse(int x, int y);
	Square* drag(Square *sqr, Points *mouse);
};

Square::Square()
{
	pts[0] = Points(0.2, 0.2);
	pts[1] = Points(0.4, 0.2);
	pts[2] = Points(0.4, 0.4);
	pts[3] = Points(0.2, 0.4);
};


void Square::draw(Square *sqr)
{
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; ++i)
	{
		glVertex2f(sqr->pts[i].x, sqr->pts[i].y);
	}
	glEnd();

	glBegin(GL_POINTS);
	for (int i = 0; i < n; ++i)
	{

		if (float(x[i])/1000.0 >= sqr->pts[0].x && float(x[i])/1000.0 <= sqr->pts[1].x && float(y[i])/1000.0 >= sqr->pts[0].y && float(y[i])/1000.0 <= sqr->pts[2].y){
			glColor3f(1, 0, 0);
		}
		else if (float(x[i]) / 1000.0 >= xo && float(x[i]) / 1000.0 <= xf && float(y[i]) / 1000.0 >= yo && float(y[i]) / 1000.0 <= yf){
			glColor3f(1, 0, 0);
		}
		else if (float(x[i]) / 1000.0 >= xf && float(x[i]) / 1000.0 <= xo && float(y[i]) / 1000.0 >= yf && float(y[i]) / 1000.0 <= yo){
			glColor3f(1, 0, 0);
		}
		else if (float(x[i]) / 1000.0 >= xo && float(x[i]) / 1000.0 <= xf && float(y[i]) / 1000.0 >= yf && float(y[i]) / 1000.0 <= yo){
			glColor3f(1, 0, 0);
		}
		else if (float(x[i]) / 1000.0 >= xf && float(x[i]) / 1000.0 <= xo && float(y[i]) / 1000.0 >= yo && float(y[i]) / 1000.0 <= yf){
			glColor3f(1, 0, 0);
		}
		else{
			glColor3f(0, 0, 1);
		}


		glVertex2f(float(x[i])/1000.0,float(y[i])/1000.0);
	}

	glEnd();
}


Points Square::mouse(int x, int y)
{
	int windowWidth = 800, windowHeight = 600;
	return Points(float(x) / windowWidth, 1.0 - float(y) / windowHeight);

}


Square* Square::drag(Square *sqr, Points *mouse)
{
	sqr->pts[0].x = mouse->x - 0.1;
	sqr->pts[0].y = mouse->y - 0.1;
	sqr->pts[1].x = mouse->x + 0.1;
	sqr->pts[1].y = mouse->y - 0.1;

	sqr->pts[3].x = mouse->x - 0.1;
	sqr->pts[3].y = mouse->y + 0.1;

	sqr->pts[2].x = mouse->x + 0.1;
	sqr->pts[2].y = mouse->y + 0.1;

	return sqr;
}


Square* sqr = new Square;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	sqr->draw(sqr);
	selection = true;
	glFlush();
}


void drag(int x, int y)
{

	Points mousePt = sqr->mouse(x, y);
	Points* mouse = &mousePt;
	if (selection){
		xo = mouse->x; yo = mouse->y;
		cout <<"inicial"<< mouse->x << "," << mouse->y << endl;
		selection = false;
	}

	xf = mouse->x; yf = mouse->y;
	cout << mouse->x << "," << mouse->y << endl;
	if (mouse->x > sqr->pts[0].x && mouse->y > sqr->pts[0].y)
	{
		if (mouse->x < sqr->pts[2].x && mouse->y < sqr->pts[2].y)
		{
			sqr->drag(sqr, mouse);
			glutPostRedisplay();
		}
	}
}

bool compare(point<int> *i, point<int> *j){
	return i->first<j->first;
}

void Initialize() {
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	srand(time(NULL));
	for (int i = 0; i < n; i++){
		x[i] = rand_nums();
		y[i] = rand_nums();
		//cout << x[i] <<","<< y[i] << endl;
	}
	//Inicialize
	vector<point<int> *> in_xs(n);
	vector<point<int> *> in_ys(n);
	cout << "Generando puntos aleatorios" << endl;
	for (int i = 0; i<n; i++){
		in_xs[i] = new point<int>(rand_nums(), nullptr);
		in_ys[i] = new point<int>(rand_nums(), in_xs[i]);
		in_xs[i]->pointer = in_ys[i];
	}
	cout << "Contruyendo RT" << endl;
	sort(in_xs.begin(), in_xs.end(), compare);
	sort(in_ys.begin(), in_ys.end(), compare);

	L_Range_T<int> LRT2D;

	LRT2D.Build_2D_RT(in_xs, in_ys);
	cout << " RT creado  " << endl;
	LRT2D.print();

}

int main(int argc, char* args[]) {

glutInit(&argc, args);
glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(400, 50);
	glutCreateWindow("Range Tree");

	glutMotionFunc(drag);

	Initialize();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
