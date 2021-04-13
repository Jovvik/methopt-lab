#include "lab2/lambda_2_function.h"

#include <doctest/doctest.h>

using namespace lab2;

TEST_CASE("fun") {
    Lambda2Function f(
        [](double x, double y) {
            return x * x + y * y + x;
        },
        [](double x, double y) {
            return std::make_pair(y, x);
        });

    CHECK_EQ(f.get_dim(), 2);
    CHECK_EQ(f(Vector({1, 2})), 6);
    CHECK_EQ(f.grad(Vector({1, 2})), Vector({2, 1}));
}
