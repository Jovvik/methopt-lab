#include <lab2/quadratic_function.h>
#include <lab3/solver.h>

using namespace lab3;

lab2::Vector classicNewton(lab2::NFunction* function, lab2::Vector x,
                           double Eps) {
    while (true) {
        const auto gradf = function->grad(x);
        const auto H     = function->hessian(x);
        const auto p     = Solver::solve(H, gradf * (-1));
        x                = x + p;
        if (p.norm() < Eps) {
            break;
        }
    }
    return x;
}