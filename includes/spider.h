//
// Created by exilio016 on 10/04/18.
//

#ifndef ARANHA2D_SPIDER_H
#define ARANHA2D_SPIDER_H


#include <GL/gl.h>

class spider {
    typedef struct {
        GLdouble x;
        GLdouble y;
    }t_point;

    typedef struct {
        t_point center;
        double radius;
    }circle;

    typedef struct {
        t_point orig;
        t_point articulation;
        t_point end;
    }leg;

private:
    circle eyes[2];
    circle cephalothorax;
    circle abdomen;
    leg legs[8];

};


#endif //ARANHA2D_SPIDER_H
