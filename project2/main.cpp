#include<GL/glut.h>
#include<math.h>
#include<iostream>
#include<Windows.h>
#define PI acos(-1)
using namespace std;
class CP2 {
public:
	CP2();
	CP2(double, double);
public:
	double x, y, w;
};
CP2::CP2()
{
}
CP2::CP2(double _x, double _y) :x(_x), y(_y), w(1) {
};

class CTransform {    //二维几何变换  
public:
	CTransform(CP2*, int);
	void Identity();
	void Translate(double, double);    //平移变换矩阵
	void Scale(double, double);          //比例变换矩阵
	void Rotate(double);                  //旋转变换矩阵
	void Rotate(double, CP2);          //相对于任意点的旋转变换矩阵
	void ReflectO();            //原点反射变换矩阵
	void ReflectX();            //X轴反射变换矩阵
	void ReflectY();            //Y轴反射变换矩阵
	void Shear(double, double);    //错切变换矩阵
	void MultiMatrix();      //矩阵相乘
	CP2* getCP2();
public:
	double T[3][3];
	CP2* POld;
	int num; //点个数
};
CTransform::CTransform(CP2* x, int y)
{
	this->POld = x;
	this->num = y;
	this->T[0][0] = 1.0; this->T[0][1] = 0.0; this->T[0][2] = 0.0;
	this->T[1][0] = 0.0; this->T[1][1] = 1.0; this->T[1][2] = 0.0;
	this->T[2][0] = 0.0; this->T[2][1] = 0.0; this->T[2][2] = 1.0;
}
void CTransform::Identity()//单位矩阵
{
	T[0][0] = 1.0; T[0][1] = 0.0; T[0][2] = 0.0;
	T[1][0] = 0.0; T[1][1] = 1.0; T[1][2] = 0.0;
	T[2][0] = 0.0; T[2][1] = 0.0; T[2][2] = 1.0;
}
void CTransform::Translate(double tx, double ty) //平移变换矩阵
{
	Identity();
	T[2][0] = tx;
	T[2][1] = ty;
	MultiMatrix();
}
void CTransform::Scale(double sx, double sy) //比例变换矩阵
{
	Identity();
	T[0][0] = sx;
	T[1][1] = sy;
	MultiMatrix();
}
void CTransform::Rotate(double beta)//旋转变换矩阵
{
	Identity();
	double rad = beta * PI / 180;
	T[0][0] = cos(rad); T[0][1] = sin(rad);
	T[1][0] = -sin(rad); T[1][1] = cos(rad);
	MultiMatrix();
}
void CTransform::Rotate(double beta, CP2 p)//相对于任意点的旋转变换矩阵
{
	Translate(-p.x, -p.y);
	Rotate(beta);
	Translate(p.x, p.y);
}
void CTransform::ReflectO()//原点反射变换矩阵
{
	Identity();
	T[0][0] = -1;
	T[1][1] = -1;
	MultiMatrix();
}
void CTransform::ReflectX()//X轴反射变换矩阵
{
	Identity();
	T[0][0] = 1;
	T[1][1] = -1;
	MultiMatrix();
}
void CTransform::ReflectY()//Y轴反射变换矩阵
{
	Identity();
	T[0][0] = -1;
	T[1][1] = 1;
	MultiMatrix();
}
void CTransform::Shear(double b, double c)//错切变换矩阵
{
	Identity();
	T[0][1] = b;
	T[1][0] = c;
	MultiMatrix();
}
void CTransform::MultiMatrix()//矩阵相乘
{
	CP2* PNew = new CP2[num];
	for (int i = 0; i < num; i++)
	{
		PNew[i] = POld[i];
	}
	for (int j = 0; j < num; j++)
	{
		POld[j].x = PNew[j].x * T[0][0] + PNew[j].y * T[1][0]
			+ PNew[j].w * T[2][0];
		POld[j].y = PNew[j].x * T[0][1] + PNew[j].y * T[1][1]
			+ PNew[j].w * T[2][1];
		POld[j].w = PNew[j].x * T[0][2] + PNew[j].y * T[1][2]
			+ PNew[j].w * T[2][2];
	}
	delete[]PNew;
}
CP2* CTransform::getCP2()
{
	return POld;
}

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
			if ((j == 25 && i == -40) ||(j==50&&i==30) || (j == 49 && i == -15)|| (j == 50 && i == -15))
			{
				continue;
			}
			if (flag)
			{
				if (judgecolor(j, i, old))
				{
					//cout << "x:" << j << "  y:" << i << endl;
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	CP2 *per,*per1, * per2,*per3,* per4,* per5,* per6;
	CP2 cp[4] = { CP2(-60,-50),CP2(-50,-50),CP2(-30,20),CP2(-20,10)};
	CTransform  p(cp, 4);
	p.Translate(125, -20);
	p.Rotate(20);
	per = p.getCP2();
	Bresenham_Line((per + 0)->x, (per + 0)->y, (per +1)->x, (per +1)->y);
	Bresenham_Line((per + 0)->x, (per + 0)->y, (per + 2)->x, (per + 2)->y);
	Bresenham_Line((per + 1)->x, (per + 1)->y, (per + 3)->x, (per + 3)->y);
	Bresenham_Line((per + 2)->x, (per + 2)->y, (per + 3)->x, (per + 3)->y);
	CP2 cp1[2] = { CP2(-20,10),CP2(20,10) };
	CTransform  p1(cp1, 2);
	p1.Scale(0.5, 0.5);
	p1.Translate(10, 5);
	per1 = p1.getCP2();
	Bresenham_Line((per1 + 0)->x, (per1 + 0)->y, (per1 + 1)->x, (per1 + 1)->y);
	CP2 cp2[2] = { CP2(-30,20),CP2(20,20) };
	CTransform  p2(cp2, 2);
	p2.Scale(0.5, 0.5);
	p2.Translate(10, 10);
	per2 = p2.getCP2();
	Bresenham_Line((per2 + 0)->x, (per2 + 0)->y, (per2 + 1)->x, (per2 + 1)->y);
	CP2 cp3[2] = { CP2(-20,-10),CP2(0,-10) };
	CTransform  p3(cp3, 2);
	p3.Translate(155,23);
	p3.Scale(0.5, 0.5);
	per3 = p3.getCP2();
	Bresenham_Line((per3 + 0)->x, (per3 + 0)->y, (per3 + 1)->x, (per3 + 1)->y);
	CP2 cp4[2] = { CP2(-30,-50),CP2(-10,-50) };
	CTransform  p4(cp4, 2);
	p4.Translate(160,0);
	p4.Scale(0.5, 0.5);
	per4 = p4.getCP2();
	Bresenham_Line((per4 + 0)->x, (per4+ 0)->y, (per4 + 1)->x, (per4 + 1)->y);
	CP2 cp5[2] = { CP2(0,-20),CP2(-10,-50)};
	CTransform  p5(cp5, 2);
	p5.Translate(76,5);
	p5.Rotate(15);
	per5 = p5.getCP2();
	Bresenham_Line((per5 + 0)->x, (per5 + 0)->y, (per5 + 1)->x, (per5 + 1)->y);
	CP2 cp6[2] = { CP2(-10,-20),CP2(-20,-50) };
	CTransform  p6(cp6, 2);
	p6.Translate(76,8);
	p6.Rotate(15);
	per6 = p6.getCP2();
	Bresenham_Line((per6 + 0)->x, (per6 + 0)->y, (per6 + 1)->x, (per6 + 1)->y);
	Bresenham_Line(-5,20,0,10);

	Bresenham_Line(30, 20, 50, 20);
	Bresenham_Line(50, 20, 50, 10);
	
	Bresenham_Line(30, 10, 50, 10);
	
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

	chuang(-30, -50, 150, 50);
	glFlush();
}
void shape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-(w / 2), (w / 2), -(h / 2), (h / 2), 0.0, 10.0);
	// gluPerspective(60, 1 * (GLfloat)w / (GLfloat)h, 1, 30)
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
