#include <doctest/doctest.h>

#include <iostream>

#include "lab2/gradient_descent.h"
#include "lab2/matrix.h"
#include "lab2/quadratic_function.h"

using namespace lab2;

std::vector<double> nigger{0, 0};  // :(
QuadraticFunction paraboloid(Matrix({{1, 0}, {0, 1}}), Vector(nigger), 1);
Vector paraboloid_start({1, 1});

QuadraticFunction fun(Matrix({{2, -1}, {-1, 2}}), Vector({4, 3}), 1);
Vector fun_start({1, 1});

std::vector<double> epsilons
    = {1, 1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8};

TEST_CASE("gradient descent") {
    std::vector<double> alphas;
    for (double a = 128; a >= 1; a /= 2.0) {
        alphas.push_back(a);
    }

    for (double a : alphas) {
        for (double epsilon : epsilons) {
            CHECK(GradientDescent(a)
                      .optimize(paraboloid, paraboloid_start, epsilon)
                      .norm()
                  <= epsilon);

            CHECK((GradientDescent(a).optimize(fun, fun_start, epsilon)
                   - Vector({-11. / 3, -10. / 3}))
                      .norm()
                  <= epsilon);
        }
    }
}
