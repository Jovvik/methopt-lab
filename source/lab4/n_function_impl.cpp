#include "lab4/n_function_impl.h"

#include <utility>

using namespace lab4;

NFunctionImpl::NFunctionImpl(
    std::size_t dim, std::function<double(lab2::Vector)> f,
    std::function<lab2::Vector(lab2::Vector)> grad_f,
    std::function<lab2::Matrix(lab2::Vector)> hessian_f)
    : dim(dim),
      f(std::move(f)),
      grad_f(std::move(grad_f)),
      hessian_f(std::move(hessian_f)) {}

lab2::Vector NFunctionImpl::grad(lab2::Vector x) { return grad_f(x); }

double NFunctionImpl::operator()(lab2::Vector x) { return f(x); }

lab2::Matrix NFunctionImpl::hessian(lab2::Vector x) { return hessian_f(x); }

std::size_t NFunctionImpl::get_dim() { return dim; }