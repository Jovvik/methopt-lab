#include "lab/quadratic_function.h"

#include <doctest/doctest.h>

#include "lab/matrix.h"

TEST_CASE("qfun") {
    auto f = lab::QuadraticFunction(lab::Matrix({{1, 0.3}, {0.4, 1.8}}),
                                    lab::Vector({1.4, -0.6}), -1.2);
    CHECK_EQ(f.get_dim(), 2);
    CHECK_EQ(f.get_call_count(), 0);
    CHECK_EQ(f.get_grad_count(), 0);
    CHECK_EQ(f(lab::Vector({1, 2})), doctest::Approx(3.8));
    CHECK_EQ(f.get_call_count(), 1);
    CHECK_EQ(f.get_grad_count(), 0);
    CHECK_EQ(f.grad(lab::Vector({1, 2})), lab::Vector({3, 3.4}));
    CHECK_EQ(f.get_call_count(), 1);
    CHECK_EQ(f.get_grad_count(), 1);
}

TEST_CASE("qfun throws") {
    CHECK_THROWS(lab::QuadraticFunction(lab::Matrix({{1, 0.3}, {0.4, 1.8}}),
                                        lab::Vector({1}), 3));
}