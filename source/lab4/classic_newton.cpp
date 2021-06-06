#include "lab4/classic_newton.h"

#include <lab3/solver.h>

#include <utility>

using namespace lab4;

ClassicNewton::ClassicNewton() : p(lab2::Vector({1})) {}

lab2::Vector ClassicNewton::iteration(lab2::NFunction& f, double) {
    lab2::Vector x    = get_points().back();
    p                 = lab3::Solver::solve(f.hessian(x), f.grad(x) * (-1));
    return x + p;
}

bool ClassicNewton::is_done(lab2::NFunction&, double epsilon) const {
    return p.norm() < epsilon;
}
