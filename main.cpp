#include <GL\glut.h>

int points = 10000;
int id = 1;
float r = 0.33333333333;
int potitionX, potitionY; 
int lastPX = 0, lastPY = 0;

//random number generator between 0.0-1.0
double randomNumber(){
	return (double)rand() / (double)RAND_MAX;
}

//fractal creator
void pentagonCreate() {
	typedef GLfloat point2[2];
	point2 vertices[5] = { {330,250},{630,250},{725,550},{480,730},{235,550} };

	int i, j;
	point2 q = { 0.0, 50.0 };
	glClear(GL_COLOR_BUFFER_BIT);
	

	for (i = 0; i < points; i++) {
		j = rand() % 5;

		q[0] = (q[0] + vertices[j][0]) * r;
		q[1] = (q[1] + vertices[j][1]) * r;

		if(points==10000)
			glColor3f(randomNumber(), randomNumber(), randomNumber());
		glBegin(GL_POINTS);
		glVertex2fv(q);
		glEnd();
	}
	
	glFlush();
}

// MENU FUNCTION
void menu(int id) {
	switch (id) {
	case 1:
		// 8000 points
		glColor3f(randomNumber(), randomNumber(), randomNumber());
		points = 8000;
		break;
	case 2:
		// 10000 points and random color
		points = 10000;
		break;
	case 3:
		// r=3/8
		r = 0.375;
		break;
	case 4:
		// r=1/3
		r = 0.33333333333;
		break;
	case 5:
		// quit
		exit(0);
	}
	
	glutPostRedisplay();
}

// LEFT CLICK ACTION
void pressLeft(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		potitionX = x - lastPX;
		potitionY = y + lastPY;
	}else{
		lastPX = x - potitionX;
		lastPY = potitionY - y;
	}
}

void drag(int x, int y) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(potitionX - x, potitionX - x + 500, -(potitionY - y), -(potitionY - y) + 500);

	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}


void myinit(void) {

	glEnable(GL_BLEND);
	glClearColor(1.0, 1.0, 1.0, 0.0); // WHITE BG
	glColor3f(0.0, 0.0, 0.0); // DRAW IN BLACK

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

}

void display(void) {
	pentagonCreate();
	glutSwapBuffers();
}

void main(int argc, char** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	
	glutInitWindowSize(500, 500);
	
	glutInitWindowPosition(0, 0); 

	glutCreateWindow("Graphics 1 - Fractals");
	
	glutDisplayFunc(display);

	glutCreateMenu(menu);

	glutMouseFunc(pressLeft);
	glutMotionFunc(drag);
	
	glutAddMenuEntry("8000 points", 1);
	glutAddMenuEntry("10000 points, random color", 2);
	glutAddMenuEntry("Pentagon, r=3/8", 3);
	glutAddMenuEntry("Pentagon, r=1/3", 4);
	glutAddMenuEntry("Quit", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	myinit();

	glutMainLoop();

}