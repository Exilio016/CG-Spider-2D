#include<GL/glut.h>
#include <spider.h>
#include <math.h>

const GLint WINDOWS_WIDTH = 800, WINDOWS_HEIGHT = 600;

void draw_circle(spider::circle *circle){
   int n_lines = 100;
   GLdouble x,y;

   x = circle->center.x + circle->radius;
   y = circle->center.y;
   glBegin(GL_TRIANGLE_STRIP);
   for(int i = 0; i <= n_lines; i++){
      glVertex2d(circle->center.x, circle->center.y);
      glVertex2d(x, y);
      x = circle->center.x + circle->radius * cos(2*M_PI*i/n_lines);
      y = circle->center.y + circle->radius * sin(2*M_PI*i/n_lines);
      glVertex2d(x,y);
   }
   glEnd();
   glFlush();
}

void draw_leg(spider::leg *leg){
   glLineWidth(5);
   glBegin(GL_LINE_STRIP);
   glVertex2d(leg->orig.x, leg->orig.y);
   glVertex2d(leg->articulation.x, leg->articulation.y);
   glVertex2d(leg->end.x, leg->end.y);
   glEnd();
   glFlush();

}

void draw_spider(spider *s){
   glColor3f(0, 0, 0);
   draw_circle(s->cephalothorax);
   draw_circle(s->abdomen);
   for(int i = 0; i < 8; i++)
      draw_leg(s->legs[i]);

   glColor3f(1,0,0);
   draw_circle(s->eyes[0]);
   draw_circle(s->eyes[1]);
}

void init(){
   glClearColor(1, 1, 1, 1);
   glMatrixMode(GL_PROJECTION);

   gluOrtho2D(0, WINDOWS_WIDTH, 0, WINDOWS_HEIGHT);
}

void callback_display(){
   spider::t_point *p = new spider::t_point;
   p->x = WINDOWS_WIDTH/2;
   p->y = WINDOWS_HEIGHT/2;

   spider *s = new spider(p);
   glClear(GL_COLOR_BUFFER_BIT);
   draw_spider(s);
   glutSwapBuffers();

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

   glutMainLoop();

   return 0;
}
