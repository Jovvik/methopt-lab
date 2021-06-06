#include "lab2/quadratic_function.h"

using namespace lab2;

QuadraticFunction::QuadraticFunction(AbstractMatrix* A, Vector&& b, double c)
    : A(A), b(b), c(c) {
    if (A->size() != b.size()) {
        throw "Size mismatch";
    }
}

std::size_t QuadraticFunction::get_dim() { return A->size(); }

double QuadraticFunction::operator()(Vector x) {
    inc_call_count();
    return *A * x * x / 2 + b * x + c;
}

Vector QuadraticFunction::grad(Vector x) {
    inc_grad_count();
    return *A * x + b;
}

Matrix QuadraticFunction::hessian(Vector) {
    size_t size = A->size();
    std::vector<std::vector<double>> result{size,
                                            {static_cast<double>(size), 0}};
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            result[i][j] = (*A)[i][j];
        }
    }
    return Matrix(result, A->max_eigenvalue());
}