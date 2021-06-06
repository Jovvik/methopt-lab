#include "lab1/brent.h"
#include "lab3/solver.h"
#include "lab4/1d_seach_newton.h"
#include "iostream"

using namespace lab4;

OneDSearchNewton::OneDSearchNewton() : p(lab2::Vector({1})) {}

lab2::Vector OneDSearchNewton::iteration(lab2::NFunction& f, double) {
    lab2::Vector x = get_points().back();
    const auto p_k = lab3::Solver::solve(f.hessian(x), f.grad(x) * (-1));
    const auto a_k = lab1::Brent(
                         [&f, x, p_k](double a) {
                             return f(x + p_k * a);
                         },
                         EPS, START, END)
                         .optimize();
    std::cout << a_k << "!\n";
    p = p_k;
    return x + p * a_k;
}

bool OneDSearchNewton::is_done(lab2::NFunction&, double epsilon) const {
    return p.norm() < epsilon;
}