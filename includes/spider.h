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
    int it;

    void draw_circle(circle *c);
    void draw_leg(leg *l);

public:
    spider(t_point *pos);
  
    void move_spider(GLint, GLint);
    void rotate_spider(GLdouble);
  
    t_point *aux_rotate(GLdouble, t_point*);
  
    void animate();
    void draw();


    void transform_leg(matrix *, leg *);
};


#endif //ARANHA2D_SPIDER_H
