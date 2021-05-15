#include <GL/glut.h>
class Point2
{
public:
	Point2();
	Point2(float, float);
public:
	GLfloat x;
	GLfloat y;
};
Point2::Point2() :x(0), y(0) {}
Point2::Point2(float a, float b) : x(a), y(b) {}
