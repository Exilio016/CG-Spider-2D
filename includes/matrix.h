//
// Created by Bruno on 12/04/2018.
//

#ifndef ARANHA2D_MATRIX_H
#define ARANHA2D_MATRIX_H


#include <GL/gl.h>
#include "types.h"

class matrix {
private:
    GLdouble **m;

public:
    int rows, cols;

    /**
     * Constructor of the class, that allocate a matrix
     * @param rows - number of rows in the matrix
     * @param cols  - number of columns in the matrix
     */
    matrix(int rows, int cols);


    /**
     * Contructor of the class, that creates a matrix of the homogeneous coordinates of a point
     * @param point - t_point of the coordinates
     */
    explicit matrix(t_point *point);

    ~matrix();

    /**
     * Method that sets a position of the matrix
     * @param row - row you want to set
     * @param col - column you want to set
     * @param val - value you want to set
     */
    void setPos(int row, int col, GLdouble val);

    /**
     * Method that sets a whole line of the matrix
     * @param row - line you want to set
     * @param vals - array containing the line, the array must have the same number of elements as the matrix columns number
     */
    void setRow(int row, GLdouble *vals);

     /**
      * Method that multiply the matrix with another one
      * @param m2 - the matrix you want to multiply
      * @return the solution matrix
      */
    matrix *multiply(matrix *m2);

    /**
     * Method that convert a 3x1 matrix into a t_point
     * @return the t_point created
     */
    t_point *toPoint();

    /**
     * Method that gets a position of the matrix
     * @param row - row you want to get
     * @param col - column you want to get
     * @return the value in the position
     */
    GLdouble getPos(int row, int col);
};


#endif //ARANHA2D_MATRIX_H
//