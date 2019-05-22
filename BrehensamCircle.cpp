#include<gl/glut.h>
class Coordinate {
private:
	int x;
	int y;
public:
	Coordinate() { x = 0; y = 0; }
	Coordinate(int x, int y) { this->x = x; this->y = y; }
	void set(int x, int y) { this->x = x; this->y = y; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	int getX() { return x; }
	int getY() { return y; }
};
class Circle {
private:
	Coordinate center;
	int radius;
public:
	Circle() { center.set(0, 0); radius = 1; }
	Circle(int centerX, int centerY, int radius) { center.set(centerX, centerY); this->radius = radius; }
	void symmetry(int x, int y);
	void midPointCircle();
};
void Circle::symmetry(int x, int y) {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2f(x + center.getX(), y + center.getY());
	glVertex2f(-x + center.getX(), y + center.getY());
	glVertex2f(x + center.getX(), -y + center.getY());
	glVertex2f(-x + center.getX(), -y + center.getY());
	glVertex2f(y + center.getY(), x + center.getX());
	glVertex2f(-y + center.getY(), x + center.getX());
	glVertex2f(y + center.getY(), -x + center.getX());
	glVertex2f(-y + center.getY(), -x + center.getX());
	glEnd();
}
void Circle::midPointCircle() {
	Coordinate point(0, radius);
	int e = 1 - radius;
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2f(center.getX(), center.getY());
	glVertex2f(center.getX(), center.getY() - radius);
	glEnd();
	while (point.getX() <= point.getY()) {
		if (e < 0)
			e += 2 * point.getX() + 3;
		else {
			e += 2 * (point.getX() - point.getY()) + 5;
			point.setY(point.getY() - 1);
		}
		point.setX(point.getX() + 1);
		symmetry(point.getX(), point.getY());
	}
	glFlush();
}
void Draw() {
	Circle circle(50, 50, 20);
	circle.midPointCircle();
}
void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Circle");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
	glutDisplayFunc(Draw);
	glutMainLoop();
}