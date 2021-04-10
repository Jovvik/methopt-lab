#include "lab/matrix.h"

#include <assert.h>

using namespace lab;

Matrix::Matrix(const std::vector<std::vector<double>>& data_) {
    for (auto v : data_) {
        data.push_back(v);
    }
}
Matrix::Matrix(std::vector<std::vector<double>>&& data_) {
    for (auto v : data_) {
        data.push_back(v);
    }
}

Vector Matrix::operator[](std::size_t idx) const { return data[idx]; }

std::size_t Matrix::size() const { return data.size(); }

Vector Matrix::operator*(Vector other) const {
    assert(size() == other.size());
    return Vector(size(), [this, &other](std::size_t i) {
        return (*this)[i] * other;
    });
}
