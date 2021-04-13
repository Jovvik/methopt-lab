#include "lab2/fastest_descent.h"

#include <utility>

lab2::FastestDescent::FastestDescent(
    std::function<std::unique_ptr<lab1::Optimizer>(
        const std::function<double(double)> &, double, double, double)>
        generator)
    : generator(std::move(generator)) {}

lab2::Vector lab2::FastestDescent::iteration(lab2::NFunction &f,
                                             double epsilon) {
    Vector x_k      = get_points().back();
    Vector grad_x_k = f.grad(x_k);
    double alpha    = generator(
                       [&f, &x_k, &grad_x_k](double alpha) {
                           return f(x_k - grad_x_k * alpha);
                       },
                       epsilon, 0, 1000)
                       ->optimize();
    return x_k - grad_x_k * alpha;
}
