#include <iostream>
#include <GL/glut.h>
#include <math.h> 

int ww = 600, wh = 400;
int xi, yi, xf, yf;

int round(double n) {
    return (n > 0.0) ? (n + 0.5) : (n - 0.5); 
}

/*void drawLine(int xa,int ya,int xb,int yb){
	glPointSize(2.0);
	glBegin(GL_POINTS);	

		glVertex2i(xa,ya);
		glVertex2i(xb,yb);	

	glEnd();
	glFlush();
}*/

void drawPixel(int x1,int y1){
	glPointSize(2.0);
	glBegin(GL_POINTS);	

		glVertex2i(x1,y1);	

	glEnd();
	glFlush();
}

void line_dda(int xa,int ya,int xb,int yb){
	int dx = xb-xa, dy = yb-ya, steps, k;
	float xincrement, yincrement, x = xa, y = ya;
	
	if(abs(dx) > abs(dy)){
		steps = abs(dx);
	}
	else{
		steps = abs(dy);
	} 
	
	xincrement = (float)dx/steps;
	yincrement = (float)dy/steps;
	
	drawPixel(round(x), round(y));
	
	for (k=0; k<steps; k++)
	{
		x += xincrement;
		y += yincrement;
		drawPixel(round(x),round(y));
	}
}

void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON )
		if (state == GLUT_DOWN) 
		{
			xi = x;
			yi = (wh-y);
		}
		else if (state == GLUT_UP) {
			xf = x;
			yf = (wh-y);
			line_dda(xi,yi,xf,yf);
		}
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q')
        exit(0);
	else if (key == 'e' || key == 'E'){
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void myinit()
{            
     glViewport(0,0,ww,wh);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);
     glMatrixMode(GL_MODELVIEW);	 
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww,wh);
	glutCreateWindow("DDA Lines");
	myinit();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard); 
	glutMainLoop();
    
	return 0;
}