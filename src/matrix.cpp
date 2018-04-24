//
// Created by Bruno on 12/04/2018.
//

#include <spider.h>
#include <stdexcept>
#include "matrix.h"

Matrix::Matrix(int rows, int cols){
    this->rows = rows; this->cols = cols;
    this->m = new GLdouble* [rows] ;

    for(int i = 0; i < rows; i++){
        this->m[i] = new GLdouble[cols];
    }
}

Matrix::Matrix(t_point *point){
    this->rows = 3; this->cols = 1;
    this->m = new GLdouble* [3];

    this->m[0] = new GLdouble[1];
    this->m[0][0] = point->x;

    this->m[1] = new GLdouble[1];
    this->m[1][0] = point->y;

    this->m[2] = new GLdouble[1];
    this->m[2][0] = 1;

}

Matrix *Matrix::multiply(Matrix *m2) {
    if(m2 == nullptr || (this->cols != m2->rows))
        return nullptr;

    Matrix *ret = new Matrix(this->rows, m2->cols);
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < m2->cols; j++){
            ret->m[i][j] = 0;
            for(int k = 0; k < this->cols; k++){
                ret->m[i][j] += this->m[i][k] * m2->m[k][j];
            }
        }
    }

    return ret;
}

void Matrix::setPos(int row, int col, GLdouble val) {
    if(row < this->rows && col < this->cols && row >= 0 && col >= 0){
        this->m[row][col] = val;
        return;
    }

    throw std::invalid_argument("Invalid matrix position!");
}

void Matrix::setRow(int row, GLdouble *vals) {
    if(row < 0 && row >= rows)
        throw std::invalid_argument("Invalid matrix row!");

    delete(this->m[row]);
    this->m[row] = vals;
}

t_point *Matrix::toPoint(){
    if(this->rows != 3 && this->cols != 1)
        throw std::invalid_argument("Impossible to convert this matrix!");

    t_point *point = new t_point;
    point->x = this->m[0][0];
    point->y = this->m[1][0];
}

GLdouble Matrix::getPos(int row, int col) {
    return this->m[row][col];
}

Matrix::~Matrix() {
    for(int i = 0; i < rows; i++)
        delete[] m[i];
    delete[] m;
}

