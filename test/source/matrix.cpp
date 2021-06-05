#include "lab2/matrix.h"

#include <doctest/doctest.h>

#include <fstream>
#include <sstream>

#include "lab2/diagonal_matrix.h"

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

TEST_CASE("matrix product size mismatch") {
    Vector trash({1});
    CHECK_THROWS(trash = mat * Vector({1}));
}

DiagonalMatrix dmat({1, 2});

TEST_CASE("matrix size") {
    CHECK_EQ(mat.size(), 2);
    CHECK_THROWS(DiagonalMatrix({}));
}

TEST_CASE("matrix operator[]") {
    Vector v = dmat[0];
    CHECK_EQ(v[0], 1);
    CHECK_EQ(v[1], 0);
}

TEST_CASE("matrix product") {
    Vector v = dmat * Vector({1, 2});
    CHECK_EQ(v[0], 1);
    CHECK_EQ(v[1], 4);
}

TEST_CASE("matrix product size mismatch") {
    Vector trash({1});
    CHECK_THROWS(trash = dmat * Vector({1}));
}

TEST_CASE("matrix file write") {
    std::ofstream of("data/test.txt");
    of << mat;
    of.close();
    std::ifstream ifs("data/test.txt");
    std::vector<std::vector<double>> read_mat;
    std::string line;
    while (getline(ifs, line)) {
        std::stringstream ss(line);
        read_mat.emplace_back();
        // technically pasted
        while (!ss.eof()) {
            read_mat.back().emplace_back();
            ss >> read_mat.back().back();
        }
    }
    CHECK_EQ(Matrix(read_mat), mat);
}
