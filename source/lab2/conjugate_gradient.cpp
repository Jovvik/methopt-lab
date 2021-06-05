#include "lab2/conjugate_gradient.h"

#include <cmath>

using namespace lab2;
Vector ConjugateGradient::iteration(NFunction& f, double) {
    Vector x = get_points().back();
    if (iteration_count == 0) {
        f_grad = f.grad(x);
        p      = f_grad * (-1);
    }
    auto* f_quad = dynamic_cast<QuadraticFunction*>(&f);
    if (f_quad == nullptr) {
        throw "F is not quadratic";
    }
    Vector t        = *(f_quad->A) * p;
    double alpha    = std::pow(f_grad.norm(), 2) / (t * p);
    Vector new_x    = x + p * alpha;
    Vector new_grad = f_grad + t * alpha;
    double beta     = std::pow(new_grad.norm(), 2) / std::pow(f_grad.norm(), 2);
    p               = new_grad * (-1) + p * beta;
    f_grad          = new_grad;
    return new_x;
}
