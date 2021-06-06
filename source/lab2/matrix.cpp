#include "lab2/matrix.h"

#include <iterator>

using namespace lab2;

Matrix Matrix::operator/(double value) { return *this * (1 / value); }

Matrix Matrix::operator-(Matrix other) { return *this + other * (-1); }

Matrix Matrix::operator+(Matrix other) {
    std::vector<std::vector<double>> new_data;
    for (size_t i = 0; i < size(); i++) {
        new_data.emplace_back(std::vector<double>());
        for (size_t j = 0; j < this->data[i].size(); j++) {
            new_data.back().emplace_back(this->data[i][j] + other.data[i][j]);
        }
    }
    return Matrix(new_data);
}

Matrix Matrix::operator*(double value) {
    std::vector<std::vector<double>> new_data;
    for (const auto& vector : this->data) {
        new_data.emplace_back(std::vector<double>());
        for (size_t j = 0; j < vector.size(); j++) {
            new_data.back().emplace_back(vector[j] * value);
        }
    }
    return Matrix(new_data);
}

Matrix Matrix::vector_mul(const Vector& first, const Vector& second) {
    auto new_data = std::vector<std::vector<double>>(
        first.size(), std::vector<double>(second.size(), 0));
    for (size_t i = 0; i < first.size(); i++) {
        for (size_t j = 0; j < second.size(); j++) {
            new_data[i][j] = first[i] * second[j];
        }
    }
    return Matrix(new_data);
}

Matrix Matrix::I(size_t size) {
    auto data
        = std::vector<std::vector<double>>(size, std::vector<double>(size, 0));
    for (size_t i = 0; i < size; i++) {
        data[i][i] = 1;
    }
    return Matrix(data);
}

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

bool Matrix::operator==(const Matrix& other) const {
    return data == other.data;
}

namespace lab2 {
    std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        copy(m.data.begin(), m.data.end(),
             std::ostream_iterator<Vector>(os, "\n"));  // not portable :(
        return os;
    }
}  // namespace lab2