#include<GL/glut.h>
#include<iostream>
using namespace std;
void swap(int& x, int& y)
{
	int t;
	t = x;
	x = y;
	y = t;
}
void drawstrline(int xc, int xz, int yc)
{
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = xc; i <= xz; i++)
	{
		glVertex2f(i, yc);
	}
	glEnd();
}
void Bresenham_Line(int xc, int yc, int xz, int yz)
{
	glBegin(GL_POINTS);
	int dx = xz - xc, dy = yz - yc;
	float k, e;
	glColor3f(1.0, 1.0, 1.0);
	if (dx == 0)
	{
		if (dy < 0)
		{
			swap(xz, xc);
			swap(yz, yc);
		}
		int t = abs(dy);
		for (int i = 0; i <= t; i++)
		{
			glVertex2d(xc, yc);
			yc++;
		}
	}
	else if (dy == 0)
	{
		if (dx < 0)
		{
			swap(xz, xc);
			swap(yz, yc);
		}
		int t = abs(dx);
		for (int i = 0; i <= t; i++)
		{
			glVertex2d(xc, yc);
			xc++;
		}
	}
	else
	{
		k = (float)dy / (float)dx;
		if (k > 0 && k < 1)
		{
			if (xz < xc)
			{
				swap(xz, xc);
				swap(yz, yc);
			}
			int t = abs(dx);
			e = -0.5;
			for (int i = 0; i <= t; i++)
			{
				glVertex2d(xc, yc);
				xc++;
				e += k;
				if (e >= 0)
				{
					yc++;
					e--;
				}
			}
		}
		else if (k >= -1 && k < 0)
		{
			if (xz < xc)
			{
				swap(xz, xc);
				swap(yz, yc);
			}
			e = 0.5;
			int t = abs(dx);
			for (int i = 0; i <= t; i++)
			{
				glVertex2d(xc, yc);
				xc++;
				e = e + k;
				if (e <= 0)
				{
					e++;
					yc--;
				}
			}
		}
		else if (k >= 1)
		{
			if (yz < yc)
			{
				swap(xz, xc);
				swap(yz, yc);
			}
			e = -0.5;
			int t = abs(dy);
			for (int i = 0; i <= t; i++)
			{
				glVertex2d(xc, yc);
				yc++;
				e = e + 1.0 / k;
				if (e > 0)
				{
					e--;
					xc++;
				}
			}
		}
		else
		{
			if (yz > yc)
			{
				swap(xz, xc);
				swap(yz, yc);
			}
			e = 0.5;
			int t = abs(dy);
			for (int i = 0; i <= t; i++)
			{
				glVertex2d(xc, yc);
				yc--;
				e = e + 1.0 / k;
				if (e < 0)
				{
					e++;
					xc++;
				}
			}

		}
	}
	glEnd();

}
int judgecolor(int x, int y, float* color)
{
	float tmp[3];
	int res = 1;
	glReadPixels(200 + x, 200 + y, 1, 1, GL_RGB, GL_FLOAT, tmp);
	for (int i = 0; i < 3; i++)
	{
		if (color[i] != tmp[i])
		{
			res = 0;
		}
	}
	return res;
}
int asd(int x, int y)
{
	if ((x == -10 && y == -20) || (x == 20 && y == 10) || (x == 20 && y == 20))
		return 1;
	return 0;
}
void chuang(int bxc, int byc, int bxz, int byz)
{
	float old[3] = { 1.0,1.0,1.0 };
	for (int i = byc; i <= byz; i++)
	{
		int t1 = 0, t2 = 0, t = 0, flag = 1;
		for (int j = bxc; j <= bxz; j++)
		{
			if (j == 25 && i == -40)
			{
				continue;
			}
			if (flag)
			{
				if (judgecolor(j, i, old))
				{
					if (t == 0) { t1 = j; t++; }
					else if (t == 1)
					{
						t2 = j;
						if (t1 + 1 == t2)
						{
							if (judgecolor(t2 + 1, i, old))
							{
								t = 0;
								flag = 0;
							}
							else t = 1;
						}
						else
						{
							if (judgecolor(t2 + 1, i, old))
							{
								t2 = ++j;
							}
							t++;
						}
					}
				}
			}
			else {
				if (!judgecolor(j, i, old) || asd(j, i)) { flag = 1; if (asd(j, i)) j--; }
			}
			if (t == 2)
			{
				drawstrline(t1 + 1, t2 - 1, i);
				t = 0;
				if ((j == 35 && i == -35) || (j == 40 && i == -20))
				{
					j--;
				}
			}
		}
	}
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Bresenham_Line(-30, 20, 20, 20);
	Bresenham_Line(30, 20, 50, 20);
	Bresenham_Line(50, 20, 50, 10);
	Bresenham_Line(-20, 10, 20, 10);
	Bresenham_Line(30, 10, 50, 10);
	Bresenham_Line(-60, -50, -30, 20);
	Bresenham_Line(-50, -50, -35, -20);
	Bresenham_Line(-30, -10, -20, 10);
	Bresenham_Line(-35, -20, -10, -20);
	Bresenham_Line(-20, -50, -10, -50);
	Bresenham_Line(0, -10, -10, -50);
	Bresenham_Line(-30, -10, 0, -10);
	Bresenham_Line(40, -50, 50, -50);
	Bresenham_Line(20, 10, 31, -24);
	Bresenham_Line(35, -35, 40, -50);
	Bresenham_Line(20, -30, 31, -24);
	Bresenham_Line(30, 10, 40, -20);
	Bresenham_Line(44, -30, 50, -50);
	Bresenham_Line(44, -30, 55, -25);
	Bresenham_Line(40, -20, 50, -15);
	Bresenham_Line(20, 20, 20, 45);
	Bresenham_Line(20, 45, 30, 45);
	Bresenham_Line(30, 45, 30, 20);
	Bresenham_Line(40, 40, 45, 45);
	Bresenham_Line(45, 45, 55, 35);
	Bresenham_Line(50, 30, 55, 35);
	Bresenham_Line(40, 40, 50, 30);
	Bresenham_Line(50, -15, 55, -25);
	Bresenham_Line(20, -30, 25, -40);
	Bresenham_Line(25, -40, 35, -35);
	Bresenham_Line(-10, -20, -20, -50);
	Bresenham_Line(-60, -50, -50, -50);

	chuang(-60, -50, 60, 50);

	glFlush();
}
void shape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, 400, 400);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-200, 200, -200, 200, 0.0, 10.0);
	// gluPerspective(60, 1 * (GLfloat)w / (GLfloat)h, 1, 30);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("the one");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutReshapeFunc(shape);
	glutDisplayFunc(display);
	glutMainLoop();
}