#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <string>
#include "point2.h"
using namespace std;
GLfloat oldx, oldy;//鼠标移动因子
GLfloat xangle = 15.0f;
GLfloat yangle = -15.0f;//旋转因子  
GLfloat zangle = 0.0f;
class  Node
{
public:
	Point2 point;
	float direction;
	Node() {}
};

GLfloat PI = 3.14;
string way[3]; 
string rule, temprule;

float len; 
float Alpha;

int n;  
Point2 pStart(0, -15); 
Node   stack[150];
int    stackpointer;

void LSystemRule()
{
	way[0] = "F[+F]F[-F]F"; 
	way[1] = "F[+F]F[-F[+F]]";
	way[2] = "FF+[+F+F]-[+F]";
	len = 1.0;
	Alpha = 25;
	n = 4;
	stackpointer = 0;
	rule = way[rand() % 3];
	for (int i = 1; i <= n; i++)
	{
		int curlen = temprule.length();
		int pos = 0, j = 0;
		while (j < curlen)
		{
			if (temprule[j] == 'F')
			{
				rule += way[rand() % 3];
				j++;
			}
			else
			{
				rule += temprule[j];
				j++;
			}
		}
		temprule = rule;
		rule.clear();
	}
	rule = temprule;
}
void drawGrass()
{
	Node  Nextnode, Curnode;
	Curnode.point.x = pStart.x;
	Curnode.point.y = pStart.y;
	Curnode.direction = 90;
	int length = rule.length();
	int  i = 0;
	glColor3f(170.0 / 255.0, 164.0 / 255.0, 111.0 / 255.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 30.0, 0.0);
	glScalef(0.7, 0.7, 1);
	glRotatef(xangle, 1.0, 0.0, 0.0);
	glRotatef(yangle, 0.0, 1.0, 0.0);//旋转
	glLineWidth(1.5);
	glPushMatrix();
	while (i < length)
	{
		switch (rule[i])
		{
		case 'F':
			Nextnode.point.x = Curnode.point.x + len * cos(Curnode.direction * PI / 180);
			Nextnode.point.y = Curnode.point.y - len * sin(Curnode.direction * PI / 180);
			Nextnode.direction = Curnode.direction;
			glBegin(GL_LINES);
			glVertex2f(Curnode.point.x, Curnode.point.y);
			glVertex2f(Nextnode.point.x, Nextnode.point.y);
			glEnd();
			Curnode = Nextnode;
			break;
		case '[':
			stack[stackpointer] = Curnode;
			stackpointer++;
			break;
		case ']':
			Curnode = stack[stackpointer - 1];
			stackpointer--;
			break;
		case '+':
			Curnode.direction = Curnode.direction + Alpha;
			break;
		case '-':
			Curnode.direction = Curnode.direction - Alpha;
			break;
		default:
			;
		}
		i++;
	}

	glPopMatrix();
}
void  display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	drawGrass();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	GLfloat f = 20.0f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-f, f, -f * (GLfloat)h / (GLfloat)w,
			f * (GLfloat)h / (GLfloat)w, -f, f);
	else
		glOrtho(-f * (GLfloat)w / (GLfloat)h,
			f * (GLfloat)w / (GLfloat)h, -f, f, -f, f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void mouse(int btn, int state, int x, int y)
{
	if ((btn == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		oldx = x; oldy = y;
	}
}
void motion(int x, int y)
{
	GLint deltax = oldx - x;
	GLint deltay = oldy - y;
	yangle += 360 * (GLfloat)deltax / (GLfloat)600;//根据屏幕上鼠标滑动的距离来设置旋转的角度  
	xangle += 360 * (GLfloat)deltay / (GLfloat)600;
	//yangle += 15;
	//xangle += 10;
	oldx = x;//记录此时的鼠标坐标，更新鼠标坐标,否则旋转将不可控 
	oldy = y;
	glutPostRedisplay();
}
int  main(int  argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("L_System");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	LSystemRule();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMainLoop();

}
