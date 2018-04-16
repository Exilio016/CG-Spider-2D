//
// Created by Bruno on 12/04/2018.
//

#ifndef ARANHA2D_TYPES_H
#define ARANHA2D_TYPES_H

#include <GL/glut.h>

typedef struct {
    GLdouble x;
    GLdouble y;
}t_point;

typedef struct {
    t_point *center;
    double radius;
}circle;

typedef struct {
    t_point *orig;
    t_point *articulation;
    t_point *end;
}leg;

bool compareDouble(double a ,double b);
#endif //ARANHA2D_TYPES_H
//