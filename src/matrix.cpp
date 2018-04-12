//
// Created by Bruno on 12/04/2018.
//

#include <spider.h>
#include <stdexcept>
#include "matrix.h"

matrix::matrix(int rows, int cols){
    this->rows = rows; this->cols = cols;
    this->m = new GLdouble* [rows] ;

    for(int i = 0; i < rows; i++){
        this->m[i] = new GLdouble[cols];
    }
}

matrix::matrix(spider::t_point *point){
    this->rows = 3; this->cols = 1;
    this->m = new GLdouble* [3];

    this->m[0] = new GLdouble[1];
    this->m[0][0] = point->x;

    this->m[1] = new GLdouble[1];
    this->m[1][0] = point->y;

    this->m[2] = new GLdouble[1];
    this->m[2][0] = 1;

}

matrix *matrix::multiply(matrix *m2) {
    if(m2 == nullptr || (this->rows != m2->cols))
        return nullptr;

    matrix *ret = new matrix(m2->rows, this->cols);
    for(int i = 0; i < m2->rows; i++){
        for(int j = 0; j < this->cols; j++){
            ret->m[i][j] = 0;
            for(int k = 0; k < this->cols; k++){
                ret->m[i][j] += this->m[i][k] * m2->m[k][j];
            }
        }
    }

    return ret;
}

void matrix::setPos(int row, int col, GLdouble val) {
    if(row < this->rows && col < this->cols && row >= 0 && col >= 0){
        this->m[row][col] = val;
        return;
    }

    throw std::invalid_argument("Invalid matrix position!");
}

void matrix::setRow(int row, GLdouble *vals) {
    if(row < 0 && row >= rows)
        throw std::invalid_argument("Invalid matrix row!");

    delete(this->m[row]);
    this->m[row] = vals;
}

spider::t_point *matrix::toPoint(){
    if(this->rows != 3 && this->cols != 1)
        throw std::invalid_argument("Impossible to convert this matrix!");

    spider::t_point *point = new spider::t_point;
    point->x = this->m[0][0];
    point->y = this->m[1][0];
}
