#include "lab2/fastest_descent.h"

#include <utility>

lab2::FastestDescent::FastestDescent(
    std::function<std::unique_ptr<lab1::Optimizer>(
        const std::function<double(double)> &, double, double, double)>
        generator)
    : generator(std::move(generator)) {}

lab2::Vector lab2::FastestDescent::iteration(QuadraticFunction &f,
                                             double epsilon) {
    Vector x_k      = get_points().back();
    Vector grad_x_k = f.grad(x_k);
    grad_x_k        = grad_x_k * (1 / grad_x_k.norm());
    double alpha
        = generator(
              [&f, &x_k, &grad_x_k](double alpha) {
                  return f(x_k - grad_x_k * alpha);
              },
              1e-6, 0,
              f.A->max_eigenvalue.has_value() ? 2. / *f.A->max_eigenvalue
                                              : 1000)
              ->optimize();
    return x_k - grad_x_k * alpha;
}
