//
// Created by exilio016 on 10/04/18.
//

#include <spider.h>
#include <cmath>
#include <iostream>
#include "spider.h"

enum {
   X,
   Y
};

#define TORAXSIZE 80
#define EYESIZE 6
#define LEGSIZE 90
#define ARTICANG 7.5
#define MAXIT 10;

spider::spider(t_point *pos) {
   this->abdomen = new circle;
   this->cephalothorax = new circle;
   this->legs = new leg*[8];
   this->eyes = new circle*[2];
   this->center = pos;

   this->abdomen->center.x = pos->x;
   this->abdomen->center.y = pos->y + TORAXSIZE - TORAXSIZE/10;
   this->abdomen->radius = TORAXSIZE;

   this->cephalothorax->center.x = pos->x;
   this->cephalothorax->center.y = pos->y - TORAXSIZE/2;
   this->cephalothorax->radius = TORAXSIZE/2;

   this->eyes[X] = new circle;
   this->eyes[X]->center.x = pos->x - EYESIZE;
   this->eyes[X]->center.y = pos->y - TORAXSIZE + EYESIZE;
   this->eyes[X]->radius = EYESIZE;

   this->eyes[Y] = new circle;
   this->eyes[Y]->center.x = pos->x + EYESIZE;
   this->eyes[Y]->center.y = pos->y - TORAXSIZE + EYESIZE;
   this->eyes[Y]->radius = EYESIZE;

   int k = 0;
   for(int i = 0; i < 8; i++){
      this->legs[i] = new leg;
      while((k >= 2 && k <= 4) || k == 9)
         k++;

      this->legs[i]->orig.x = this->cephalothorax->center.x
         + cos(k*M_PI/6)
         * this->cephalothorax->radius;

      this->legs[i]->orig.y = this->cephalothorax->center.y
         - sin(k*M_PI/6)
         * this->cephalothorax->radius;

      if(k < 3 || k > 9) {
         this->legs[i]->end.x = this->legs[i]->orig.x + LEGSIZE;
         this->legs[i]->articulation.x = this->legs[i]->orig.x + LEGSIZE/2;
      }
      else{
         this->legs[i]->end.x = this->legs[i]->orig.x - LEGSIZE;
         this->legs[i]->articulation.x = this->legs[i]->orig.x - LEGSIZE/2;
      }

      this->legs[i]->end.y = this->legs[i]->orig.y + LEGSIZE/2;
      this->legs[i]->articulation.y = this->legs[i]->orig.y - ARTICANG;


      if(k == 1 || k == 5) {
         this->legs[i]->articulation.y = this->legs[i]->orig.y - 3 * LEGSIZE / 2;
         this->legs[i]->end.y = this->legs[i]->articulation.y - ARTICANG;
      }

      if(k == 8 || k == 10)
         this->legs[i]->end.y = this->legs[i]->orig.y + 3*LEGSIZE/2;

      k++;
   }
}

t_point spider::aux_rotate(GLdouble angle, t_point init) {
   t_point result;
   t_point axis = *(this->center);
   result.x = cos(angle) * init.x - sin(angle) * init.y +
      axis.x * (1 - cos(angle)) + axis.y * sin(angle);
   result.y = sin(angle) * init.x + cos(angle) * init.y +
      axis.y * (1 - cos(angle)) - axis.x * sin(angle);
   return result;
}

void spider::rotate_spider(GLdouble angle) {
   t_point aux;

   aux = aux_rotate(angle, this->abdomen->center); 
   this->abdomen->center.x = aux.x;
   this->abdomen->center.y = aux.y;

   aux = aux_rotate(angle, this->cephalothorax->center); 
   this->cephalothorax->center.x = aux.x;
   this->cephalothorax->center.y = aux.y;

   aux = aux_rotate(angle, this->eyes[X]->center); 
   this->eyes[X]->center.x = aux.x;
   this->eyes[X]->center.y = aux.y;

   aux = aux_rotate(angle, this->eyes[Y]->center); 
   this->eyes[Y]->center.x = aux.x;
   this->eyes[Y]->center.y = aux.y;

   for(int i = 0; i < 8; i++) {
      aux = aux_rotate(angle, this->legs[i]->orig); 
      this->legs[i]->orig.x = aux.x;
      this->legs[i]->orig.y = aux.y;

      aux = aux_rotate(angle, this->legs[i]->articulation); 
      this->legs[i]->articulation.x = aux.x;
      this->legs[i]->articulation.y = aux.y;

      aux = aux_rotate(angle, this->legs[i]->end); 
      this->legs[i]->end.x = aux.x;
      this->legs[i]->end.y = aux.y;
   }
}

void spider::move_spider(GLint x, GLint y) {
   while (this->center->x != x && this->center-> y != y) {
      std::cout<<"click\n";
      rotate_spider(M_PI/4);
      break;
   }
}

void spider::draw_circle(circle *circle){
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

void spider::draw_leg(leg *leg){
    glLineWidth(5);
    glBegin(GL_LINE_STRIP);
    glVertex2d(leg->orig.x, leg->orig.y);
    glVertex2d(leg->articulation.x, leg->articulation.y);
    glVertex2d(leg->end.x, leg->end.y);
    glEnd();
    glFlush();

}

void spider::draw(){
    glColor3f(0, 0, 0);
    draw_circle(this->cephalothorax);
    draw_circle(this->abdomen);
    for(int i = 0; i < 8; i++)
        draw_leg(this->legs[i]);

    glColor3f(1,0,0);
    draw_circle(this->eyes[0]);
    draw_circle(this->eyes[1]);
}

void spider::animate() {


}