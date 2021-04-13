#include "lab2/gradient_descent.h"

using namespace lab2;

Vector GradientDescent::iteration(NFunction &f) {
    Vector x = points_last(), y = x - f.grad(x) * a;
    while (f(y) >= f(x)) {
        a /= 2;
        x = points_last();
        y = x - f.grad(x) * a;
    }
    return y;
}

lab2::Vector GradientDescent::points_last() const {
    return get_points().back();
}
