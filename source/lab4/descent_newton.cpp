#include "lab4/descent_newton.h"

#include "iostream"
#include "lab1/brent.h"
#include "lab3/solver.h"

using namespace lab4;

DescentNewton::DescentNewton() : p(lab2::Vector({1})) {}

lab2::Vector DescentNewton::iteration(lab2::NFunction& f, double) {
    lab2::Vector x    = get_points().back();
    lab2::Vector grad = f.grad(x);
    lab2::Vector d    = grad * (-1);
    p                 = lab3::Solver::solve(f.hessian(x), d);
    if (p * grad < 0) {
        d = p;
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