#include "lab2/fastest_descent.h"

#include <utility>

lab2::FastestDescent::FastestDescent(
    std::function<std::unique_ptr<lab1::Optimizer>(
        const std::function<double(double)> &, double, double, double)>
        generator)
    : generator(std::move(generator)) {}

lab2::Vector lab2::FastestDescent::iteration(NFunction &f, double) {
    Vector x_k       = get_points().back();
    Vector grad_x_k  = f.grad(x_k);
    double grad_norm = grad_x_k.norm();
    grad_x_k         = grad_x_k * (1 / grad_norm);

    auto *f_quad = dynamic_cast<QuadraticFunction *>(&f);

    double alpha = generator(
                       [&f, &x_k, &grad_x_k](double alpha) {
                           return f(x_k - grad_x_k * alpha);
                       },
                       1e-6, 0,
                       f_quad == nullptr || !f_quad->A->has_max_eigenvalue
                           ? 10
                           : 2. / f_quad->A->max_eigenvalue() * grad_norm)
                       ->optimize();
    return x_k - grad_x_k * alpha;
}
