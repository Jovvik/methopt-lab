#include "lab2/quadratic_function.h"

#include <doctest/doctest.h>

#include "lab2/matrix.h"

using namespace lab2;

TEST_CASE("qfun") {
    auto f = QuadraticFunction(new Matrix({{1, 0.3}, {0.4, 1.8}}),
                               Vector({1.4, -0.6}), -1.2);
    CHECK_EQ(f.get_dim(), 2);
    CHECK_EQ(f.get_call_count(), 0);
    CHECK_EQ(f.get_grad_count(), 0);
    CHECK_EQ(f(Vector({1, 2})), doctest::Approx(3.8));
    CHECK_EQ(f.get_call_count(), 1);
    CHECK_EQ(f.get_grad_count(), 0);
    CHECK_EQ(f.grad(Vector({1, 2})), Vector({3, 3.4}));
    CHECK_EQ(f.get_call_count(), 1);
    CHECK_EQ(f.get_grad_count(), 1);
}

TEST_CASE("qfun throws") {
    CHECK_THROWS(
        QuadraticFunction(new Matrix({{1, 0.3}, {0.4, 1.8}}), Vector({1}), 3));
}
