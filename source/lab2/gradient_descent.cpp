#include "lab2/gradient_descent.h"

using namespace lab2;

Vector GradientDescent::iteration(NFunction &f, double) {
    Vector x   = points_last();
    Vector y   = x - f.grad(x) * a;
    double f_x = f(x);
    while (f(y) >= f_x && iteration_count <= 1000) {
        a /= 2;
        y = x - f.grad(x) * a;
        iteration_count++;
    }
    return y;
}

lab2::Vector GradientDescent::points_last() const {
    return get_points().back();
}
