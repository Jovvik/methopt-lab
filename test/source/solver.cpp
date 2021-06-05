#include "lab3/solver.h"

#include <doctest/doctest.h>
#include <lab2/vector.h>

using namespace lab2;
using namespace lab3;

TEST_CASE("Solver stub") {
    CHECK_EQ(Vector({-4, 4.5}), Solver::solve(Matrix({{1, 2}, {3, 4}}), Vector({5, 6})));
}