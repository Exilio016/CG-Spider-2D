#include<GL/glut.h>
#include <spider.h>
#include <cmath>
#include <matrix.h>
#include <iostream>

const GLint WINDOWS_WIDTH = 800, WINDOWS_HEIGHT = 600;

spider *s;


void init(){
   glClearColor(1, 1, 1, 1);
   glMatrixMode(GL_PROJECTION);

   t_point *p = new t_point;
   p->x = WINDOWS_WIDTH/2;
   p->y = WINDOWS_HEIGHT/2;

   s = new spider(p);

   gluOrtho2D(0, WINDOWS_WIDTH, WINDOWS_HEIGHT, 0);
}

void callback_display(){
   glClear(GL_COLOR_BUFFER_BIT);
   s->draw();
   glutSwapBuffers();
}

/*Function that associates other functions to
 * react to the mouse inputs*/
void mouseClick(GLint button, GLint action, GLint x, GLint y) {
   //GLUT_DOWN
   //GLUT_UP
   if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
      glutPostRedisplay();
      s->move_spider(x, y);
      s->draw();
   }
}


/*Function that is called if the mouse is pressed
 * and moving */
void mouseDrag(GLint x, GLint y) {
   //std::cout<<"drag x:"<<x<<" y:"<<y<<"\n";
}

int main(int argc, char *argv[]){
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

   GLint screen_width = glutGet(GLUT_SCREEN_WIDTH),
         screen_height = glutGet(GLUT_SCREEN_HEIGHT);

   glutInitWindowPosition((screen_width - WINDOWS_WIDTH)/2, (screen_height - WINDOWS_HEIGHT)/2);
   glutInitWindowSize(WINDOWS_WIDTH, WINDOWS_HEIGHT);
   glutCreateWindow("Aranha 2D");

   init();
   glutDisplayFunc(callback_display);

   glutMouseFunc(mouseClick);
   glutMotionFunc(mouseDrag);

   glutMainLoop();

   return 0;
}
