#include "lab2/matrix.h"

#include <iterator>

using namespace lab2;

Matrix::Matrix(const std::vector<std::vector<double>>& data_,
               std::optional<double> max_eigenvalue)
    : AbstractMatrix(max_eigenvalue) {
    for (const auto& v : data_) {
        data.emplace_back(v);
    }
    check_size();
}

Matrix::Matrix(std::size_t size,
               const std::function<double(std::size_t, std::size_t)>& generator)
    : AbstractMatrix(std::nullopt) {
    data.reserve(size);
    for (std::size_t i = 0; i < size; i++) {
        data.push_back(
            Vector(size, std::bind(generator, i, std::placeholders::_1)));
    }
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

bool Matrix::operator==(const Matrix& other) const { return data == other.data; }

namespace lab2 {
    std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        copy(m.data.begin(), m.data.end(),
             std::ostream_iterator<Vector>(os, "\n")); // not portable :(
        return os;
    }
}
