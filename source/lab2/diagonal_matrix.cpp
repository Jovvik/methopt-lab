#include "lab2/diagonal_matrix.h"

using namespace lab2;

DiagonalMatrix::DiagonalMatrix(const std::vector<double>& diagonal,
                               std::optional<double> max_eigenvalue)
    : AbstractMatrix(max_eigenvalue), diagonal(diagonal) {
    if (diagonal.size() == 0) {
        throw "Matrix is empty";
    }
}

Vector DiagonalMatrix::operator[](std::size_t idx) const {
    double val = diagonal[idx];
    return Vector(size(), [idx, val](std::size_t i) {
        if (i == idx) {
            return val;
        }
        return 0.;
    });
}

std::size_t DiagonalMatrix::size() const { return diagonal.size(); }

Vector DiagonalMatrix::operator*(Vector other) const {
    if (size() != other.size()) {
        throw "Size mismatch";
    }
    return Vector(size(), [this, &other](std::size_t idx) {
        return this->diagonal[idx] * other[idx];
    });
}
