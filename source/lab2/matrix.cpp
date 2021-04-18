#include "lab2/matrix.h"

using namespace lab2;

Matrix::Matrix(const std::vector<std::vector<double>>& data_,
               std::optional<double> max_eigenvalue)
    : AbstractMatrix(max_eigenvalue) {
    for (const auto& v : data_) {
        data.emplace_back(v);
    }
    check_size();
}

Vector Matrix::operator[](std::size_t idx) const { return data[idx]; }

std::size_t Matrix::size() const { return data.size(); }

Vector Matrix::operator*(Vector other) const {
    if (size() != other.size()) {
        throw "Size mismatch";
    }
    return Vector(size(), [this, &other](std::size_t i) {
        return (*this)[i] * other;
    });
}

void Matrix::check_size() const {
    if (size() == 0) {
        throw "Matrix is empty";
    }
    if (size() != (*data.begin()).size()
        || !std::equal(data.begin() + 1, data.end(), data.begin(),
                       [](const Vector& lhs, const Vector& rhs) {
                           return lhs.size() == rhs.size();
                       })) {
        throw "Matrix rows have different sizes";
    }
}
