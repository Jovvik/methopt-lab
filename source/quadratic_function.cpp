#include "lab/quadratic_function.h"

using namespace lab;

QuadraticFunction::QuadraticFunction(Matrix&& A, Vector&& b, double c)
    : A(A), b(b), c(c) {
    if (A.size() != b.size()) {
        throw "Size mismatch";
    }
}

std::size_t QuadraticFunction::get_dim() { return A.size(); }

double QuadraticFunction::operator()(Vector x) {
    inc_call_count();
    return A * x * x / 2 + b * x + c;
}

Vector QuadraticFunction::grad(Vector x) {
    inc_grad_count();
    return A * x + b;
}