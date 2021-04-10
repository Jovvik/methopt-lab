#include "lab/vector.h"

#include <doctest/doctest.h>

TEST_CASE("size") {
    CHECK_EQ(lab::Vector({1, 2, 3}).size(), 3);
    CHECK_EQ(lab::Vector({}).size(), 0);
}

TEST_CASE("operator[]") { CHECK_EQ(lab::Vector({1, 2, 3})[0], 1); }

TEST_CASE("dot product") {
    double sum = lab::Vector({0.1, 0.2}) * lab::Vector({0.3, 0.4});
    CHECK_EQ(sum, doctest::Approx(0.11));
}

TEST_CASE("add") {
    lab::Vector res = lab::Vector({1, 2}) + lab::Vector({3, 4});
    CHECK_EQ(res[0], 4);
    CHECK_EQ(res[1], 6);
}