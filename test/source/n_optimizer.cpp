#include <doctest/doctest.h>

#include <algorithm>
#include <iostream>

#include "lab1/brent.h"
#include "lab1/dichotomy.h"
#include "lab1/fibonacci.h"
#include "lab1/golden_ratio.h"
#include "lab1/optimizer.h"
#include "lab2/conjugate_gradient.h"
#include "lab2/fastest_descent.h"
#include "lab2/functions.h"
#include "lab2/gradient_descent.h"
#include "lab2/matrix.h"
#include "lab2/quadratic_function.h"
#include "lab4/1d_seach_newton.h"
#include "lab4/classic_newton.h"
#include "lab4/descent_newton.h"
#include "lab4/dfp.h"
#include "lab4/powell.h"

using namespace lab2;
using namespace lab4;

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

std::vector<double> zero_vector{0, 0};

std::vector<double> epsilons = {1, 1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6};
std::vector<std::pair<QuadraticFunction*, Vector>> fns
    = {{&Functions::paraboloid, zero_vector},
       {&Functions::f1, Vector({-11. / 3, -10. / 3})}};

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
            for (auto& starting_point : starting_points) {
                for (auto& [f, ans] : fns) {
                    CHECK((GradientDescent(a).optimize(*f, starting_point,
                                                       epsilon)
                           - ans)
                              .norm()
                          <= epsilon);
                }
            }
        }
    }
}

TEST_CASE("fastest descent") {
    std::vector<Vector> starting_points;
    for (double x = 0.5; x <= 4; x *= 2) {
        for (double y = 0.5; y <= 4; y *= 2) {
            starting_points.emplace_back(std::vector{x, y});
        }
    }

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

    for (double epsilon : epsilons) {
        for (const Vector& starting_point : starting_points) {
            for (auto& [f, ans] : fns) {
                CHECK((FastestDescent(generator).optimize(*f, starting_point,
                                                          epsilon)
                       - ans)
                          .norm()
                      <= epsilon);
            }
        }
    }
}

TEST_CASE("conjugate") {
    std::vector<Vector> starting_points;
    for (double x = 0.5; x <= 4; x *= 2) {
        for (double y = 0.5; y <= 4; y *= 2) {
            starting_points.emplace_back(std::vector{x, y});
        }
    }

    for (double epsilon : epsilons) {
        for (const Vector& starting_point : starting_points) {
            for (auto& [f, ans] : fns) {
                CHECK((ConjugateGradient().optimize(*f, starting_point, epsilon)
                       - ans)
                          .norm()
                      <= epsilon);
            };
            QuadraticFunction f(new Matrix({{422, -420}, {-420, 422}}),
                                Vector({-192, 50}), -25);
            CHECK((ConjugateGradient().optimize(f, starting_point, epsilon)
                   - Vector({15006. / 421, 14885. / 421}))
                      .norm()
                  <= epsilon);
        }
    }
}

TEST_CASE("classic newton") {
    std::vector<double> less_epsilons = {1, 1e-4, 1e-8};
    std::vector<Vector> starting_points;
    for (double x = 0.5; x <= 2; x *= 2) {
        for (double y = 0.5; y <= 2; y *= 2) {
            starting_points.emplace_back(std::vector{x, y});
        }
    }
    for (double epsilon : less_epsilons) {
        for (const Vector& starting_point : starting_points) {
            for (auto& [f, ans] : fns) {
                CHECK((ClassicNewton().optimize(*f, starting_point, epsilon)
                       - ans)
                          .norm()
                      <= epsilon);
            }
        }
    }
}

TEST_CASE("one d search newton") {
    std::vector<double> less_epsilons = {1, 1e-4, 1e-8};
    std::vector<Vector> starting_points;
    for (double x = 0.5; x <= 2; x *= 2) {
        for (double y = 0.5; y <= 2; y *= 2) {
            starting_points.emplace_back(std::vector{x, y});
        }
    }
    for (double epsilon : less_epsilons) {
        for (const Vector& starting_point : starting_points) {
            for (auto& [f, ans] : fns) {
                CHECK((OneDSearchNewton().optimize(*f, starting_point, epsilon)
                       - ans)
                          .norm()
                      <= epsilon);
            }
        }
    }
}

TEST_CASE("test") {
    std::cout << DFP().optimize(Functions::f_2_1,
                                          lab2::Vector({10, 10}), 1e-8);
    std::cout << DFP().optimize(Functions::f_2_1,
                                lab2::Vector({10, -10}), 1e-8);
    std::cout << DFP().optimize(Functions::f_2_1,
                                lab2::Vector({-10, 10}), 1e-8);
    std::cout << DFP().optimize(Functions::f_2_1,
                                lab2::Vector({-10, -10}), 1e-8);
}

TEST_CASE("descent newton") {
    std::vector<double> less_epsilons = {1, 1e-4, 1e-7};
    std::vector<Vector> starting_points;
    for (double x = 0.5; x <= 2; x *= 2) {
        for (double y = 0.5; y <= 2; y *= 2) {
            starting_points.emplace_back(std::vector{x, y});
        }
    }
    for (double epsilon : less_epsilons) {
        for (const Vector& starting_point : starting_points) {
            for (auto& [f, ans] : fns) {
                CHECK((DescentNewton().optimize(*f, starting_point, epsilon)
                       - ans)
                          .norm()
                      <= epsilon);
            }
        }
    }
}

TEST_CASE("DFP method") {
    std::vector<double> less_epsilons = {1, 1e-4, 1e-8};
    std::vector<Vector> starting_points;
    for (double x = 0.5; x <= 2; x *= 2) {
        for (double y = 0.5; y <= 2; y *= 2) {
            starting_points.emplace_back(std::vector{x, y});
        }
    }
    for (double epsilon : less_epsilons) {
        for (const Vector& starting_point : starting_points) {
            for (auto& [f, ans] : fns) {
                CHECK((DFP().optimize(*f, starting_point, epsilon) - ans).norm()
                      <= epsilon);
            }
        }
    }
}

TEST_CASE("Powell's method") {
    std::vector<double> less_epsilons = {1, 1e-4, 1e-8};
    std::vector<Vector> starting_points;
    for (double x = 0.5; x <= 2; x *= 2) {
        for (double y = 0.5; y <= 2; y *= 2) {
            starting_points.emplace_back(std::vector{x, y});
        }
    }
    for (double epsilon : less_epsilons) {
        for (const Vector& starting_point : starting_points) {
            for (auto& [f, ans] : fns) {
                CHECK((Powell().optimize(*f, starting_point, epsilon) - ans)
                          .norm()
                      <= epsilon);
            }
        }
    }
}