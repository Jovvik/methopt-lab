#include "lab4/descent_newton.h"

#include "iostream"
#include "lab1/brent.h"
#include "lab3/solver.h"

using namespace lab4;

DescentNewton::DescentNewton() : p(lab2::Vector({1})) {}

lab2::Vector DescentNewton::iteration(lab2::NFunction& f, double) {
    const lab2::Vector x = get_points().back(), grad = f.grad(x),
                       anti_grad = grad * (-1);
    auto d                       = anti_grad;
    if (iteration_count == 0) {
        const double r = lab1::Brent(
                             [&f, &x, p_ = d](double a) {
                                 return f(x + p_ * a);
                             },
                             ONE_DIM_EPS, ONE_DIM_START, ONE_DIM_END)
                             .optimize();
        p = d * r;
        return x + p;
    }
    p = lab3::Solver::solve(f.hessian(x), anti_grad);
    if (p * grad < 0) {
        d = p;
    } else {
        d = anti_grad;
    }
    const double r = lab1::Brent(
                         [&f, &x, p_ = d](double a) {
                             return f(x + p_ * a);
                         },
                         ONE_DIM_EPS, ONE_DIM_START, ONE_DIM_END)
                         .optimize();
    p = d * r;
    return x + p;
}

bool DescentNewton::is_done(lab2::NFunction&, double epsilon) const {
    return p.norm() < epsilon;
}