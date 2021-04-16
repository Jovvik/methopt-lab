#include "lab2/gradient_descent.h"

using namespace lab2;

Vector GradientDescent::iteration(QuadraticFunction &f, double) {
    Vector x        = points_last();
    Vector f_x_grad = f.grad(x);
    f_x_grad        = f_x_grad;
    Vector y        = x - f_x_grad * a;
    double f_x      = f(x);
    while (f(y) >= f_x && iteration_count <= 1000) {
        a /= 2;
        y = x - f_x_grad * a;
        iteration_count++;
    }
    return y;
}

lab2::Vector GradientDescent::points_last() const {
    return get_points().back();
}
