//
// Created by exilio016 on 10/04/18.
//

#ifndef ARANHA2D_SPIDER_H
#define ARANHA2D_SPIDER_H

#include <GL/gl.h>
#include "types.h"
#include "matrix.h"

class spider {
public:

    circle **eyes;
    circle *cephalothorax;
    circle *abdomen;
    leg **legs;
    t_point *center;

private:
    typedef enum {
        stopped,
        walking_left,
        walking_dir
    }state;

    state currentState;
    state oldState;
    t_point *point;
    double ang;
    int it;

    void draw_circle(circle *c);
    void draw_leg(leg *l);

public:
    explicit spider(t_point *pos);
    ~spider();
  
    void move_spider();
    void rotate_spider(GLdouble);
  
    t_point *aux_rotate(GLdouble, t_point*);
    int find_direction(t_point *point);
  
    void animate();
    void draw();


    void transform_leg(matrix *, leg *);

    void aux_move();

    void transform(matrix *pMatrix);

    void setDestination(t_point *p);
};


#endif //ARANHA2D_SPIDER_H
