#include "lab2/function_2d.h"

#include <cmath>
#include <memory>

#include "lab2/functions.h"

using namespace lab2;

Function2D::Function2D(QuadraticFunction *f_2d) : f(f_2d) {
    if (f->A->size() != 2) {
        throw "not a 2d function";
    }
}

double Function2D::operator()(double x, double y) {
    return f->operator()(Vector({x, y}));
}

std::pair<double, double> Function2D::get_y(double x, double z) {
    double t1 = (*f->A)[0][1] * x + (*f->A)[1][0] * x + 2 * f->b[1],
           t2 = (*f->A)[0][0] * x * x + 2 * f->b[0] * x + 2 * f->c - 2 * z;
    if ((*f->A)[1][1] == 0) {
        return {-t2 / t1, -t2 / t1};
    }
    double t3 = sqrt(t1 * t1 - 4 * (*f->A)[1][1] * t2);
    return {(-t3 - t1) / (2 * (*f->A)[1][1]), (t3 - t1) / (2 * (*f->A)[1][1])};
}