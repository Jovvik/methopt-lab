#include "lab2/vector.h"

#include <doctest/doctest.h>

#include <fstream>

using namespace lab2;

TEST_CASE("vector size") {
    CHECK_EQ(Vector({1, 2, 3}).size(), 3);
    CHECK_THROWS(Vector({}));
}

TEST_CASE("vector operator[]") { CHECK_EQ(Vector({1, 2, 3})[0], 1); }

TEST_CASE("vector dot product") {
    double sum = Vector({0.1, 0.2}) * Vector({0.3, 0.4});
    CHECK_EQ(sum, doctest::Approx(0.11));

    CHECK_THROWS(Vector({1, 2}) * Vector({0.5}));
}

TEST_CASE("vector add") {
    Vector res = Vector({1, 2}) + Vector({3, 4});
    CHECK_EQ(res[0], 4);
    CHECK_EQ(res[1], 6);

    CHECK_THROWS(Vector({1, 2}) + Vector({0.5}));
}

TEST_CASE("vector diff") {
    Vector res = Vector({1, 2}) - Vector({4, 3});
    CHECK_EQ(res, Vector({-3, -1}));

    CHECK_THROWS(Vector({1, 2}) - Vector({0.5}));
}

TEST_CASE("vector reference constructor") {
    std::vector<double> v{1, 2};
    Vector res = Vector(v);
    CHECK_EQ(res[0], 1);
    CHECK_EQ(res[1], 2);
}

TEST_CASE("vector scale") {
    Vector res = Vector({1, 2}) * 3;
    CHECK_EQ(res[0], 3);
    CHECK_EQ(res[1], 6);
}

TEST_CASE("vector norm") { CHECK_EQ(Vector({3, 4}).norm(), 5); }

TEST_CASE("vector file write") {
    std::ofstream of("data/tmp.txt");
    of << Vector({1, 2, 3});
    of.close();
    std::ifstream ifs("data/tmp.txt");
    CHECK_EQ(Vector({1, 2, 3}), Vector(ifs));
}