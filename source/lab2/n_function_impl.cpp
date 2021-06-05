#include "lab2/n_function_impl.h"

using namespace lab2;

NFunctionImpl::NFunctionImpl(int dim, const std::function<double(Vector)>& f,
                             const std::function<Vector(Vector)>& grad_f,
                             const std::function<Matrix(Vector)>& hessian_f)
    : dim(dim), f(f), grad_f(grad_f), hessian_f(hessian_f) {}

Vector NFunctionImpl::grad(Vector x) { return this->grad_f.operator()(x); }

double NFunctionImpl::operator()(Vector x) { return this->f.operator()(x); }

Matrix NFunctionImpl::hessian(Vector x) {
    return this->hessian_f.operator()(x);
}

std::size_t NFunctionImpl::get_dim() { return dim; }