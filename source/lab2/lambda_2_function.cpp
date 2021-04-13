#include <lab2/lambda_2_function.h>

#include <utility>

using namespace lab2;

Lambda2Function::Lambda2Function(
    std::function<double(double, double)> f,
    std::function<std::pair<double, double>(double, double)> grad)
    : f(std::move(f)), f_grad(std::move(grad)) {}

double Lambda2Function::operator()(Vector x) { return f(x[0], x[1]); }

Vector Lambda2Function::grad(Vector x) {
    auto [a, b] = f_grad(x[0], x[1]);
    return Vector({a, b});
}

std::size_t Lambda2Function::get_dim() { return 2; }
