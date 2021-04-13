#include <cxxopts.hpp>
#include <iostream>
#include <optional>

#include "lab1/brent.h"
#include "lab1/optimizer.h"

int main() {
    std::function<std::unique_ptr<lab1::Optimizer>(
        const std::function<double(double)>&, double, double, double)>
        f = [](const std::function<double(double)>& optimized_function,
               double epsilon, double start, double end) {
            return std::make_unique<lab1::Brent>(optimized_function, epsilon,
                                                 start, end);
        };
}
