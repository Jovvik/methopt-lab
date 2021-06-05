#include "lab3/solver.h"

#include <doctest/doctest.h>
#include <lab2/vector.h>

using namespace lab2;
using namespace lab3;

TEST_CASE("Solver") {
    Vector result = Solver::solve(Matrix({{1, 2}, {3, 4}}), Vector({5, 6}));
    CHECK_EQ(result.size(), 2);
    CHECK_EQ(result[0], doctest::Approx(-4.0));
    CHECK_EQ(result[1], doctest::Approx(4.5));
}