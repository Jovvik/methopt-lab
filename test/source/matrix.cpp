#include "lab2/matrix.h"

#include <doctest/doctest.h>

using namespace lab2;

Matrix mat = Matrix({{1, 2}, {3, 4}});

TEST_CASE("matrix size") {
    CHECK_EQ(mat.size(), 2);
    CHECK_THROWS(Matrix({}));
    CHECK_THROWS(Matrix({{1, 2}, {3}}));
}

TEST_CASE("matrix reference constructor") {
    std::vector<std::vector<double>> vv = {{1, 2}, {3, 4}};
    Matrix mat(vv);
    CHECK_EQ(mat[0][0], 1);
    CHECK_EQ(mat[0][1], 2);
    CHECK_EQ(mat[1][0], 3);
    CHECK_EQ(mat[1][1], 4);
}

TEST_CASE("matrix operator[]") {
    Vector v = mat[0];
    CHECK_EQ(v[0], 1);
    CHECK_EQ(v[1], 2);
}

TEST_CASE("matrix product") {
    Vector v = mat * Vector({1, 2});
    CHECK_EQ(v[0], 5);
    CHECK_EQ(v[1], 11);
}

TEST_CASE("matrix product size mismatch") { CHECK_THROWS(mat * Vector({1})); }