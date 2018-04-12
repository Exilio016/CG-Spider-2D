//
// Created by exilio016 on 10/04/18.
//

#include <spider.h>
#include <cmath>
#include "spider.h"

#define TORAXSIZE 80
#define EYESIZE 6
#define LEGSIZE 90
#define ARTICANG 7.5
#define MAXIT 10;

spider::spider(spider::t_point *pos) {
    this->abdomen = new circle;
    this->cephalothorax = new circle;
    this->legs = new leg*[8];
    this->eyes = new circle*[2];

    this->center = pos;
    this->it = 0;
    this->currentState = stopped;
    this->oldState = stopped;

    this->abdomen->center.y = pos->y - TORAXSIZE + TORAXSIZE/10;
    this->abdomen->center.x = pos->x;
    this->abdomen->radius = TORAXSIZE;

    this->cephalothorax->center.y = pos->y + TORAXSIZE/2;
    this->cephalothorax->center.x = pos->x;
    this->cephalothorax->radius = TORAXSIZE/2;

    this->eyes[0] = new circle;
    this->eyes[0]->center.y = pos->y + TORAXSIZE - EYESIZE;
    this->eyes[0]->center.x = pos->x - EYESIZE;
    this->eyes[0]->radius = EYESIZE;

    this->eyes[1] = new circle;
    this->eyes[1]->center.y = pos->y + TORAXSIZE - EYESIZE;
    this->eyes[1]->center.x = pos->x + EYESIZE;
    this->eyes[1]->radius = EYESIZE;

    int k = 0;
    for(int i = 0; i < 8; i++){
        this->legs[i] = new leg;
        while((k >= 2 && k <= 4) || k == 9)
            k++;

        this->legs[i]->orig.x = this->cephalothorax->center.x
                               + cos(k*M_PI/6)
                                 * this->cephalothorax->radius;

        this->legs[i]->orig.y = this->cephalothorax->center.y
                               + sin(k*M_PI/6)
                                 * this->cephalothorax->radius;

        if(k < 3 || k > 9) {
            this->legs[i]->end.x = this->legs[i]->orig.x + LEGSIZE;
            this->legs[i]->articulation.x = this->legs[i]->orig.x + LEGSIZE/2;
        }
        else{
            this->legs[i]->end.x = this->legs[i]->orig.x - LEGSIZE;
            this->legs[i]->articulation.x = this->legs[i]->orig.x - LEGSIZE/2;
        }

        this->legs[i]->end.y = this->legs[i]->orig.y - LEGSIZE/2;
        this->legs[i]->articulation.y = this->legs[i]->orig.y + ARTICANG;


        if(k == 1 || k == 5) {
            this->legs[i]->articulation.y = this->legs[i]->orig.y + LEGSIZE;
            this->legs[i]->end.y = this->legs[i]->articulation.y + ARTICANG;
        }

        if(k == 8 || k == 10)
            this->legs[i]->end.y = this->legs[i]->orig.y - 3*LEGSIZE/2;


        k++;
    }

}

void spider::draw_circle(spider::circle *circle){
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

void spider::draw_leg(spider::leg *leg){
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