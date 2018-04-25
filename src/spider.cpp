//
// Created by exilio016 on 10/04/18.
//

#include <spider.h>
#include <cmath>
#include <iostream>
#include <matrix.h>
#include <types.h>
#include <limits>
#include "spider.h"

enum {
   X,
   Y
};

#define TORAXSIZE 40
#define EYESIZE 3
#define LEGSIZE 45
#define ARTICANG 3.75
#define MAXIT 3

void scaleMatrix(double s, t_point *p, Matrix *m){
    if(m != nullptr && m->rows == 3 && m->cols == 3){
        m->setRow(0, new GLdouble[3]{s, 0, p->x * (1 - s)});
        m->setRow(1, new GLdouble[3]{0, s, p->y * (1 - s)});
        m->setRow(2, new GLdouble[3]{0, 0, 1});
    }
}

void rotateMatrix(double ang, t_point *p, Matrix *m){
    if(m != nullptr && m->rows == 3 && m->cols == 3) {
        m->setRow(0, new GLdouble[3]{cos(ang), -sin(ang),  p->x - p->x * cos(ang) + p->y * sin(ang)});
        m->setRow(1, new GLdouble[3]{sin(ang), cos(ang), p->y - p->y * cos(ang) - p->x * sin(ang)});
        m->setRow(2, new GLdouble[3]{0, 0, 1});
    }
}

void translateMatrix(t_point *t, Matrix *m){
    if(m != nullptr && m->rows == 3 && m->cols == 3) {
        m->setRow(0, new GLdouble[3]{1, 0 ,t->x});
        m->setRow(1, new GLdouble[3]{0, 1 ,t->y});
        m->setRow(2, new GLdouble[3]{0, 0 ,1});

    }
}

Spider::Spider(t_point *pos) {
   this->abdomen = new circle;
   this->cephalothorax = new circle;
   this->legs = new leg*[8];
   this->eyes = new circle*[2];
   this->center = pos;
   this->destination = new t_point;
   this->ang = 0;

   this->destination->x = pos->x;
   this->destination->y = pos->y;

   this->abdomen->center = new t_point;
   this->abdomen->center->x = pos->x;
   this->abdomen->center->y = pos->y + TORAXSIZE - TORAXSIZE/10;
   this->abdomen->radius = TORAXSIZE;

   this->cephalothorax->center = new t_point;
   this->cephalothorax->center->x = pos->x;
   this->cephalothorax->center->y = pos->y - TORAXSIZE/2;
   this->cephalothorax->radius = TORAXSIZE/2;

   this->eyes[0] = new circle;
   this->eyes[0]->center = new t_point;
   this->eyes[0]->center->x = pos->x - EYESIZE;
   this->eyes[0]->center->y = pos->y - TORAXSIZE + EYESIZE;
   this->eyes[0]->radius = EYESIZE;

   this->eyes[1] = new circle;
   this->eyes[1]->center = new t_point;
   this->eyes[1]->center->x = pos->x + EYESIZE;
   this->eyes[1]->center->y = pos->y - TORAXSIZE + EYESIZE;
   this->eyes[1]->radius = EYESIZE;

   int k = 0;
   for(int i = 0; i < 8; i++){
      this->legs[i] = new leg;
      while((k >= 2 && k <= 4) || k == 9)
         k++;

      this->legs[i]->orig = new t_point;
      this->legs[i]->articulation = new t_point;
      this->legs[i]->end = new t_point;

      this->legs[i]->orig->x = this->cephalothorax->center->x
         + cos(k*M_PI/6)
         * this->cephalothorax->radius;

      this->legs[i]->orig->y = this->cephalothorax->center->y
         - sin(k*M_PI/6)
         * this->cephalothorax->radius;

      if(k < 3 || k > 9) {
         this->legs[i]->end->x = this->legs[i]->orig->x + LEGSIZE;
         this->legs[i]->articulation->x = this->legs[i]->orig->x + LEGSIZE/2;
      }
      else{
         this->legs[i]->end->x = this->legs[i]->orig->x - LEGSIZE;
         this->legs[i]->articulation->x = this->legs[i]->orig->x - LEGSIZE/2;
      }

      this->legs[i]->end->y = this->legs[i]->orig->y + LEGSIZE/2;
      this->legs[i]->articulation->y = this->legs[i]->orig->y - ARTICANG;


      if(k == 1 || k == 5) {
         this->legs[i]->articulation->y = this->legs[i]->orig->y - LEGSIZE;
         this->legs[i]->end->y = this->legs[i]->articulation->y - ARTICANG;
      }

      if(k == 8 || k == 10)
         this->legs[i]->end->y = this->legs[i]->orig->y + 3*LEGSIZE/2;

      k++;
   }
}

t_point *Spider::aux_rotate(GLdouble angle, t_point *init) {
   t_point *result = new t_point;
   t_point *axis = (this->center);
   result->x = cos(angle) * init->x - sin(angle) * init->y +
      axis->x * (1 - cos(angle)) + axis->y * sin(angle);
   result->y = sin(angle) * init->x + cos(angle) * init->y +
      axis->y * (1 - cos(angle)) - axis->x * sin(angle);
   return result;
}

void Spider::transform_leg(Matrix *transform, leg *m_leg){
    if(transform == nullptr || transform->rows != 3 || transform->cols != 3)
        throw std::invalid_argument("Illegal transformation matrix!");

    Matrix *orig = new Matrix(m_leg->orig);
    Matrix *articulation = new Matrix(m_leg->articulation);
    Matrix *end = new Matrix(m_leg->end);

    delete(m_leg->orig);
    delete(m_leg->articulation);
    delete(m_leg->end);

    Matrix *aux = transform->multiply(orig);
    m_leg->orig = aux->toPoint();
    delete(aux);

    aux = transform->multiply(articulation);
    m_leg->articulation = aux->toPoint();
    delete(aux);

    aux = transform->multiply(end);
    m_leg->end = aux->toPoint();

    delete(aux);
    delete(orig);
    delete(articulation);
    delete(end);
}

void Spider::rotate_spider(GLdouble angle) {
   t_point *aux;

   aux = aux_rotate(angle, this->abdomen->center); 
   this->abdomen->center->x = aux->x;
   this->abdomen->center->y = aux->y;

   aux = aux_rotate(angle, this->cephalothorax->center); 
   this->cephalothorax->center->x = aux->x;
   this->cephalothorax->center->y = aux->y;

   aux = aux_rotate(angle, this->eyes[X]->center); 
   this->eyes[0]->center->x = aux->x;
   this->eyes[0]->center->y = aux->y;

   aux = aux_rotate(angle, this->eyes[Y]->center); 
   this->eyes[1]->center->x = aux->x;
   this->eyes[1]->center->y = aux->y;

   for(int i = 0; i < 8; i++) {
      aux = aux_rotate(angle, this->legs[i]->orig); 
      this->legs[i]->orig->x = aux->x;
      this->legs[i]->orig->y = aux->y;

      aux = aux_rotate(angle, this->legs[i]->articulation); 
      this->legs[i]->articulation->x = aux->x;
      this->legs[i]->articulation->y = aux->y;

      aux = aux_rotate(angle, this->legs[i]->end); 
      this->legs[i]->end->x = aux->x;
      this->legs[i]->end->y = aux->y;
   }
   this->ang += angle;
}

void Spider::aux_move(){
    Matrix *t = new Matrix(3,3);
    GLdouble tx, ty;
    tx = 0; ty = -TORAXSIZE/3;
    
    t_point *point = new t_point;
    point->x = tx; point->y = ty;

    Matrix *ap = new Matrix(point);
    Matrix *ar = new Matrix(3, 3);

    t_point *vNull = new t_point; vNull->x = 0; vNull->y = 0;
    rotateMatrix(ang, vNull, ar);
    /*
    ar->setRow(0, new GLdouble[3]{cos(ang), -sin(ang), 0});
    ar->setRow(1, new GLdouble[3]{sin(ang),  cos(ang), 0});
    ar->setRow(2, new GLdouble[3]{0,         0 ,       1});
     */

    Matrix *aux = ar->multiply(ap);
    delete(point);
    point = aux->toPoint();

    tx = point->x; ty = point->y;
    translateMatrix(point, t);
    delete(point);
/*
    t->setRow(0, new GLdouble[3]{1, 0, tx});
    t->setRow(1, new GLdouble[3]{0, 1, ty});
    t->setRow(2, new GLdouble[3]{0, 0, 1});
*/
    this->transform(t);
}

void Spider::move_spider() {
    this->walking = true;

    if((center->x < destination->x+TORAXSIZE) && (center->y < destination->y + TORAXSIZE ) &&
      (center->x > destination->x-TORAXSIZE) && (center->y > destination->y - TORAXSIZE )) {
        this->walking = false;
        return;
    }

    int signal = find_direction(destination);
    rotate_spider(signal*M_PI/24);
    this->aux_move();
}

void Spider::draw_circle(circle *circle){
    int n_lines = 100;
    GLdouble x,y;

    x = circle->center->x + circle->radius;
    y = circle->center->y;
    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i <= n_lines; i++){
        glVertex2d(circle->center->x, circle->center->y);
        glVertex2d(x, y);
        x = circle->center->x + circle->radius * cos(2*M_PI*i/n_lines);
        y = circle->center->y + circle->radius * sin(2*M_PI*i/n_lines);
        glVertex2d(x,y);
    }
    glEnd();
    glFlush();
}

void Spider::draw_leg(leg *leg){
    glLineWidth(5);
    glBegin(GL_LINE_STRIP);
    glVertex2d(leg->orig->x, leg->orig->y);
    glVertex2d(leg->articulation->x, leg->articulation->y);
    glVertex2d(leg->end->x, leg->end->y);
    glEnd();
    glFlush();
}

void Spider::draw(){
    glColor3f(0, 0, 0);
    draw_circle(this->cephalothorax);
    draw_circle(this->abdomen);
    for(int i = 0; i < 8; i++)
        draw_leg(this->legs[i]);

    glColor3f(1,0,0);
    draw_circle(this->eyes[0]);
    draw_circle(this->eyes[1]);
}


void Spider::walk_left(double rotAng){
    double su = 1.15;
    double sd = 0.85;
    Matrix *sm = new Matrix(3, 3);
    Matrix *rm = new Matrix(3, 3);
    Matrix *aux;

    //Rotate and scale on front left leg
    rotateMatrix(rotAng, this->legs[2]->orig, rm);
    scaleMatrix(sd, this->legs[2]->orig, sm);
    aux = rm->multiply(sm);
    transform_leg(aux, this->legs[2]);
    delete(aux);

    //Rotate inner legs
    rotateMatrix(-rotAng/2, this->legs[3]->orig, rm);
    transform_leg(rm, this->legs[3]);

    rotateMatrix(rotAng/2, this->legs[4]->orig, rm);
    transform_leg(rm, this->legs[4]);

    //Rotate and scale on back left leg
    rotateMatrix(rotAng, this->legs[5]->orig, rm);
    scaleMatrix(sd, this->legs[5]->orig, sm);
    aux = rm->multiply(sm);
    transform_leg(aux, this->legs[5]);
    delete(aux);

    //Rotate and scale on front right leg
    rotateMatrix(rotAng, this->legs[1]->orig, rm);
    scaleMatrix(su, this->legs[1]->orig, sm);
    aux = rm->multiply(sm);
    transform_leg(aux, this->legs[1]);
    delete(aux);

    //Rotate inner legs
    rotateMatrix(-rotAng/2, this->legs[0]->orig, rm);
    transform_leg(rm, this->legs[0]);

    rotateMatrix(rotAng/2, this->legs[7]->orig, rm);
    transform_leg(rm, this->legs[7]);

    //Rotate and scale on back left leg
    rotateMatrix(rotAng, this->legs[6]->orig, rm);
    scaleMatrix(su, this->legs[6]->orig, sm);
    aux = rm->multiply(sm);
    transform_leg(aux, this->legs[6]);
    delete(aux);
}

void Spider::walk_right(double rotAng){
    double su = 1.15;
    double sd = 0.85;
    Matrix *sm = new Matrix(3, 3);
    Matrix *rm = new Matrix(3, 3);
    Matrix *aux;

    //Rotate and scale on front left leg
    rotateMatrix(-rotAng, this->legs[2]->orig, rm);
    scaleMatrix(su, this->legs[2]->orig, sm);
    aux = rm->multiply(sm);
    transform_leg(aux, this->legs[2]);
    delete(aux);

    //Rotate inner legs
    rotateMatrix(rotAng/2, this->legs[3]->orig, rm);
    transform_leg(rm, this->legs[3]);

    rotateMatrix(-rotAng/2, this->legs[4]->orig, rm);
    transform_leg(rm, this->legs[4]);

    //Rotate and scale on back left leg
    rotateMatrix(-rotAng, this->legs[5]->orig, rm);
    scaleMatrix(su, this->legs[5]->orig, sm);
    aux = rm->multiply(sm);
    transform_leg(aux, this->legs[5]);
    delete(aux);

    //Rotate and scale on front right leg
    rotateMatrix(-rotAng, this->legs[1]->orig, rm);
    scaleMatrix(sd, this->legs[1]->orig, sm);
    aux = rm->multiply(sm);
    transform_leg(aux, this->legs[1]);
    delete(aux);

    //Rotate inner legs
    rotateMatrix(rotAng/2, this->legs[0]->orig, rm);
    transform_leg(rm, this->legs[0]);

    rotateMatrix(-rotAng/2, this->legs[7]->orig, rm);
    transform_leg(rm, this->legs[7]);

    //Rotate and scale on back left leg
    rotateMatrix(-rotAng, this->legs[6]->orig, rm);
    scaleMatrix(sd, this->legs[6]->orig, sm);
    aux = rm->multiply(sm);
    transform_leg(aux, this->legs[6]);
    delete(aux);
}

void Spider::animate() {
    double rang = M_PI/53;

    this->it++;
    if(this->currentState == stopped){
        if(this->it <= MAXIT) {
            if (this->oldState == walking_dir)
                this->walk_left(rang);
            else
                this->walk_right(rang);
        }
        else{
            if(it == 4) {
                Matrix *reescale = new Matrix(3, 3);
                scaleMatrix(1.07, this->legs[2]->orig, reescale);
                transform_leg(reescale, this->legs[2]);
                scaleMatrix(1.07, this->legs[1]->orig, reescale);
                transform_leg(reescale, this->legs[1]);
                scaleMatrix(1.07, this->legs[5]->orig, reescale);
                transform_leg(reescale, this->legs[5]);
                scaleMatrix(1.07, this->legs[6]->orig, reescale);
                transform_leg(reescale, this->legs[6]);
                delete (reescale);
            }

            if(this->walking){
                this->it = 0;

                if(this->oldState == walking_dir)
                    this->currentState = walking_left;
                else
                    this->currentState = walking_dir;
            }
        }
    }

    else if(this->currentState == walking_left){
        if(this->it <= MAXIT) {
            this->walk_left(rang);
        }
        else{
            this->it = 0;
            this->currentState = stopped;
            this->oldState = walking_left;
        }
    }

    else {
        if(this->it <= MAXIT) {
            this->walk_right(rang);
        }
        else{
            this->it = 0;
            this->currentState =stopped;
            this->oldState = walking_dir;
        }
    }
}

Spider::~Spider() {
    delete (this->abdomen->center);
    delete (this->cephalothorax->center);
    delete(this->eyes[0]->center);
    delete(this->eyes[1]->center);
    delete(this->eyes[0]);
    delete(this->eyes[1]);

    for(int i = 0; i < 8; i++){
        delete(this->legs[i]->orig);
        delete(this->legs[i]->articulation);
        delete(this->legs[i]->end);
        delete (this->legs[i]);
    }
    delete (this->abdomen);
    delete (this->cephalothorax);
    delete[] (this->eyes);
    delete[] (this->legs);
}

int Spider::find_direction(t_point *point) {
    Matrix *p = new Matrix(point);
    Matrix *t = new Matrix(3, 3);
    Matrix *r = new Matrix(3, 3);
    GLdouble x = this->center->x;
    GLdouble y = this->center->y;

    t_point *tp = new t_point; tp->x = -x; tp->y = -y;
    translateMatrix(tp, t);
    /*
    t->setRow(0, new GLdouble[3]{1, 0 ,-x});
    t->setRow(1, new GLdouble[3]{0, 1 ,-y});
    t->setRow(2, new GLdouble[3]{0, 0 ,1});
    */

    rotateMatrix(-ang, this->center, r);
    /*
    r->setRow(0, new GLdouble[3]{cos(-ang), -sin(-ang), x - x*cos(-ang) + y*sin(-ang)});
    r->setRow(1, new GLdouble[3]{sin(-ang),  cos(-ang), y - y*cos(-ang) - x*sin(-ang)});
    r->setRow(2, new GLdouble[3]{0,         0 ,       1});
    */

    Matrix *aux = t->multiply(r);

    delete(t);
    delete(r);
    t = aux;

    aux = t->multiply(p);
    delete(p);
    t_point *auxp = aux->toPoint();
    delete(aux);

    if( fabs(auxp->x) <= TORAXSIZE) {
        int ret = 0;
        if(auxp->y > 0)
            ret = 1;
       delete(auxp);
       return ret;
    }
    if(auxp->x > TORAXSIZE) {
        delete(auxp);
        return 1;
    }
    delete(auxp);
    return -1;
}

void aux_transform(Matrix *m, t_point **point){
    Matrix *p = new Matrix(*point);
    Matrix *aux = m->multiply(p);

    delete(*point);
    *point = aux->toPoint();
    delete(aux);
    delete(p);

}

void Spider::transform(Matrix *pMatrix) {
    aux_transform(pMatrix, &this->center);
    aux_transform(pMatrix, &this->cephalothorax->center);
    aux_transform(pMatrix, &this->abdomen->center);
    aux_transform(pMatrix, &this->eyes[0]->center);
    aux_transform(pMatrix, &this->eyes[1]->center);

    for(int i = 0; i < 8; i++){
        this->transform_leg(pMatrix, this->legs[i]);
    }
}

void Spider::setDestination(t_point *p) {
    if(p != nullptr){
        delete(destination);
        destination = p;
    }
}
