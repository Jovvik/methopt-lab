#include <doctest/doctest.h>

#include <algorithm>
#include <iostream>

#include "lab1/brent.h"
#include "lab1/dichotomy.h"
#include "lab1/fibonacci.h"
#include "lab1/golden_ratio.h"
#include "lab1/optimizer.h"
#include "lab1/parabola.h"
#include "lab2/fastest_descent.h"
#include "lab2/gradient_descent.h"
#include "lab2/matrix.h"
#include "lab2/quadratic_function.h"

using namespace lab2;

#define DOCTEST_VALUE_PARAMETERIZED_DATA(data, data_container)               \
    static size_t _doctest_subcase_idx = 0;                                  \
    std::for_each(                                                           \
        data_container.begin(), data_container.end(), [&](const auto& in) {  \
            DOCTEST_SUBCASE((std::string(#data_container "[")                \
                             + std::to_string(_doctest_subcase_idx++) + "]") \
                                .c_str()) {                                  \
                data = in;                                                   \
            }                                                                \
        });                                                                  \
    _doctest_subcase_idx = 0

std::vector<double> zero_vector{0, 0};  // :(
QuadraticFunction paraboloid(Matrix({{1, 0}, {0, 1}}), Vector(zero_vector), 1);
Vector paraboloid_start({1, 1});

QuadraticFunction fun(Matrix({{2, -1}, {-1, 2}}), Vector({4, 3}), 1);
Vector fun_start({1, 1});

std::vector<std::pair<QuadraticFunction, Vector>> fns
    = {{paraboloid, zero_vector}, {fun, Vector({-11. / 3, -10. / 3})}};

std::vector<double> epsilons = {1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6};

TEST_CASE("gradient descent") {
    std::vector<double> alphas;
    for (double a = 128; a >= 1; a /= 2.0) {
        alphas.push_back(a);
    }

    std::vector<Vector> starting_points;
    for (double x = 0.5; x <= 4; x *= 2) {
        for (double y = 0.5; y <= 4; y *= 2) {
            starting_points.emplace_back(std::vector{x, y});
        }
    }

    for (double a : alphas) {
        for (double epsilon : epsilons) {
            for (const Vector& starting_point : starting_points) {
                for (auto& [f, ans] : fns) {
                    CHECK(
                        (GradientDescent(a).optimize(f, starting_point, epsilon)
                         - ans)
                            .norm()
                        <= epsilon);
                }
            }
        }
    }
}

TEST_CASE("fastest descent") {
    using Gen = std::function<std::unique_ptr<lab1::Optimizer>(
        const std::function<double(double)>&, double, double, double)>;
    Gen generator;
    // kill me
    std::vector<Gen> generators
        = {[](const std::function<double(double)>& optimized_function,
              double epsilon, double start, double end) {
               return std::make_unique<lab1::Brent>(optimized_function, epsilon,
                                                    start, end);
           },
           [](const std::function<double(double)>& optimized_function,
              double epsilon, double start, double end) {
               return std::make_unique<lab1::Dichotomy>(optimized_function,
                                                        epsilon, start, end);
           },
           [](const std::function<double(double)>& optimized_function,
              double epsilon, double start, double end) {
               return std::make_unique<lab1::Fibonacci>(optimized_function,
                                                        epsilon, start, end);
           },
           [](const std::function<double(double)>& optimized_function,
              double epsilon, double start, double end) {
               return std::make_unique<lab1::GoldenRatio>(optimized_function,
                                                          epsilon, start, end);
           }};

    DOCTEST_VALUE_PARAMETERIZED_DATA(generator, generators);

    std::vector<Vector> starting_points;
    for (double x = 0.5; x <= 4; x *= 2) {
        for (double y = 0.5; y <= 4; y *= 2) {
            starting_points.emplace_back(std::vector{x, y});
        }
    }

    for (double epsilon : epsilons) {
        for (const Vector& starting_point : starting_points) {
            for (auto& [f, ans] : fns) {
                CHECK((FastestDescent(generator).optimize(f, starting_point,
                                                          epsilon)
                       - ans)
                          .norm()
                      <= epsilon);
            }
        }
    }
}