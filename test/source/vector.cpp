#include "lab/vector.h"

#include <doctest/doctest.h>

TEST_CASE("vector size") {
    CHECK_EQ(lab::Vector({1, 2, 3}).size(), 3);
    CHECK_EQ(lab::Vector({}).size(), 0);
}

TEST_CASE("vector operator[]") { CHECK_EQ(lab::Vector({1, 2, 3})[0], 1); }

TEST_CASE("vector dot product") {
    double sum = lab::Vector({0.1, 0.2}) * lab::Vector({0.3, 0.4});
    CHECK_EQ(sum, doctest::Approx(0.11));

    CHECK_THROWS(lab::Vector({}) * lab::Vector({0.5}));
}

TEST_CASE("vector add") {
    lab::Vector res = lab::Vector({1, 2}) + lab::Vector({3, 4});
    CHECK_EQ(res[0], 4);
    CHECK_EQ(res[1], 6);

    CHECK_THROWS(lab::Vector({}) + lab::Vector({0.5}));
}

TEST_CASE("vector reference constror") {
    std::vector<double> v{1, 2};
    lab::Vector res = lab::Vector(v);
    CHECK_EQ(res[0], 1);
    CHECK_EQ(res[1], 2);
}

TEST_CASE("vector scale") {
    lab::Vector res = lab::Vector({1, 2}) * 3;
    CHECK_EQ(res[0], 3);
    CHECK_EQ(res[1], 6);
}