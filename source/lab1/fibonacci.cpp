#include "lab1/fibonacci.h"

#include <cmath>

using namespace lab1;

Fibonacci::Fibonacci(const func& optimized_function, double epsilon,
                     double start, double end)
    : GoldenRatio(optimized_function, epsilon, start, end) {
    initial_start = start;
    initial_end = end;
    n = std::ceil(std::log((end - start) / epsilon * std::sqrt(5))
                  / std::log((1 + std::sqrt(5)) / 2));
}

bool Fibonacci::is_done() { return steps_count >= n; }

double Fibonacci::get_x1(double start, double end) {
    return start
           + fib(n - steps_count + 1) / fib(n - steps_count + 3)
                 * (end - start);
}

double Fibonacci::get_x2(double start, double end) {
    return start
           + fib(n - steps_count + 2) / fib(n - steps_count + 3)
                 * (end - start);
}

double Fibonacci::fib(int n) {
    return (std::pow((1 + std::sqrt(5)), n) - std::pow((1 - std::sqrt(5)), n))
           / std::pow(2, n) / std::sqrt(5);
}
