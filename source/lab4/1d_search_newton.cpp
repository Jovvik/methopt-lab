#include "iostream"
#include "lab1/brent.h"
#include "lab3/solver.h"
#include "lab4/1d_seach_newton.h"

using namespace lab4;

OneDSearchNewton::OneDSearchNewton() : p(lab2::Vector({1})) {}

lab2::Vector OneDSearchNewton::iteration(lab2::NFunction& f, double) {
    lab2::Vector x   = get_points().back();
    p                = lab3::Solver::solve(f.hessian(x), f.grad(x) * (-1));
    const auto alpha = lab1::Brent(
                           [&f, &x, p_ = p](double a) {
                               return f(x + p_ * a);
                           },
                           ONE_DIM_EPS, ONE_DIM_START, ONE_DIM_END)
                           .optimize();
    p = p * alpha;
    return x + p;
}

bool OneDSearchNewton::is_done(lab2::NFunction&, double epsilon) const {
    return p.norm() < epsilon;
}