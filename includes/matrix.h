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
    int rows, cols;

public:
    matrix(int rows, int cols);
    matrix(t_point *point);

    void setPos(int row, int col, GLdouble val);
    void setRow(int row, GLdouble *vals);

    matrix *multiply(matrix *m2);

    t_point *toPoint();

    GLdouble getPos(int row, int col);
};


#endif //ARANHA2D_MATRIX_H
//