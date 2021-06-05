#include "lab2/n_function_impl.h"

#include <utility>

using namespace lab2;

NFunctionImpl::NFunctionImpl(std::size_t dim, std::function<double(Vector)> f,
                             std::function<Vector(Vector)> grad_f,
                             std::function<Matrix(Vector)> hessian_f)
    : dim(dim),
      f(std::move(f)),
      grad_f(std::move(grad_f)),
      hessian_f(std::move(hessian_f)) {}

Vector NFunctionImpl::grad(Vector x) { return grad_f(x); }

double NFunctionImpl::operator()(Vector x) { return f(x); }

Matrix NFunctionImpl::hessian(Vector x) { return hessian_f(x); }

std::size_t NFunctionImpl::get_dim() { return dim; }