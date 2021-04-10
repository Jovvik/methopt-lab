#include "lab/matrix.h"

#include <doctest/doctest.h>

lab::Matrix mat = lab::Matrix({{1, 2}, {3, 4}});

TEST_CASE("matrix size") {
    CHECK_EQ(mat.size(), 2);
    CHECK_THROWS(lab::Matrix({}));
}

TEST_CASE("matrix reference constructor") {
    std::vector<std::vector<double>> vv = {{1, 2}, {3, 4}};
    lab::Matrix mat(vv);
    CHECK_EQ(mat[0][0], 1);
    CHECK_EQ(mat[0][1], 2);
    CHECK_EQ(mat[1][0], 3);
    CHECK_EQ(mat[1][1], 4);
}

TEST_CASE("matrix operator[]") {
    lab::Vector v = mat[0];
    CHECK_EQ(v[0], 1);
    CHECK_EQ(v[1], 2);
}

TEST_CASE("matrix product") {
    lab::Vector v = mat * lab::Vector({1, 2});
    CHECK_EQ(v[0], 5);
    CHECK_EQ(v[1], 11);
}

TEST_CASE("matrix product size mismatch") {
    CHECK_THROWS(mat * lab::Vector({1}));
}