//
// Created by exilio016 on 15/04/18.
//

#include <types.h>
#include <limits>
#include <cmath>

bool compareDouble(double a, double b) {
    return (fabs(a- b) <= std::numeric_limits<double>::epsilon());
}