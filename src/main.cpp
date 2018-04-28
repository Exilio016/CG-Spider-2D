#include<GL/glut.h>
#include <spider.h>
#include <cmath>
#include <matrix.h>
#include <iostream>

#define FRAMES 24

const GLint WINDOWS_WIDTH = 800, WINDOWS_HEIGHT = 600;

Spider *s;


void init(){
   glClearColor(1, 1, 1, 1);
   glMatrixMode(GL_PROJECTION);

   auto *p = new t_point;
   p->x = (double) WINDOWS_WIDTH/2;
   p->y = (double) WINDOWS_HEIGHT/2;

   s = new Spider(p);

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

      auto *p = new t_point;
      p->x = x; 
      p->y = y;

      s->setDestination(p); //Destination of the spider
      glutPostRedisplay();
      //s->move_spider();
      s->draw();
   }
}


/*Function that is called if the mouse is pressed
 * and moving */
void mouseDrag(GLint x, GLint y) {
   
      auto *p = new t_point;
      p->x = x; 
      p->y = y;

      s->setDestination(p); //Destination of the spider
      glutPostRedisplay();
      //s->move_spider();
      s->draw();
   //std::cout<<"drag x:"<<x<<" y:"<<y<<"\n";
}

void move_spider(int ref){
    if(ref == 0)
        return;

    glutPostRedisplay();
    s->animate();       //Animation of the spider walking
    s->move_spider();   //Moving the spider to the destination
    s->draw();          //Showing the spider on the screen
    glutTimerFunc(1000/FRAMES, move_spider, 1);
}

int main(int argc, char *argv[]){
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // NOLINT

    GLint screen_width = glutGet(GLUT_SCREEN_WIDTH),
         screen_height = glutGet(GLUT_SCREEN_HEIGHT);

   glutInitWindowPosition((screen_width - WINDOWS_WIDTH)/2, (screen_height - WINDOWS_HEIGHT)/2);
   glutInitWindowSize(WINDOWS_WIDTH, WINDOWS_HEIGHT);
   glutCreateWindow("Aranha 2D");

   init();
   glutDisplayFunc(callback_display);

   glutMouseFunc(mouseClick);
   glutMotionFunc(mouseDrag);
   glutTimerFunc(1000/FRAMES, move_spider, 1);

   glutMainLoop();

   return 0;
}

