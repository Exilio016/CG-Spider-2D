//
// Created by exilio016 on 10/04/18.
//

#ifndef ARANHA2D_SPIDER_H
#define ARANHA2D_SPIDER_H

#include <GL/gl.h>
#include "types.h"
#include "matrix.h"

class spider {

private:
    circle **eyes;
    circle *cephalothorax;
    circle *abdomen;
    leg **legs;
    t_point *center;

    typedef enum {
        stopped,
        walking_left,
        walking_dir
    }state;

    state currentState;
    state oldState;
    t_point *destination;
    double ang;

    /**
     * Method that draws on the screen a circle
     * @param c - the circle you wants to draw
     */
    void draw_circle(circle *c);

    /**
     * Method that draws non the screen a leg
     * @param l - the leg you wants to draw
     */
    void draw_leg(leg *l);

    //todo document this method
    t_point *aux_rotate(GLdouble a, t_point* p);

    /**
     * Method that calculate if the spider will rotate to the left or the right
     * based on a destination point
     * @param point - the destination point
     * @return 1 - to rotate to the left, -1 to the right and 0 to not rotate
     */
    int find_direction(t_point *point);

    /**
     * Method that calculates a transformation in a leg of the spider
     * @param m - the transformation matrix
     * @param l - the leg you wants to transform
     */
    void transform_leg(matrix *m, leg *l);

    /**
     * Method that applies a transformation in the spider
     * @param pMatrix - the transformation matrix
     */
    void transform(matrix *pMatrix);

    void aux_move();

public:

    /**
     * Constructor of the class, it sets the points of the spider
     * @param pos - t_point with the coordinates you want to draws the spider
     */
    explicit spider(t_point *pos);
    ~spider();

    /**
     * Method that moves the spider into the direction of the attribute t_point *destination
     * The destination can be set with the method setDestination()
     */
    void move_spider();

    /**
     * Method that rotates the spider
     * @param a - the angle of rotation, in radians
     */
    void rotate_spider(GLdouble a);

    /**
     * Method that animates the spider legs
     */
    void animate();

    /**
     * Method that draws the spider on the screen
     */
    void draw();

    /**
     * Method that sets the destination point of the spider
     * @param p - the destination point
     */
    void setDestination(t_point *p);
};


#endif //ARANHA2D_SPIDER_H
