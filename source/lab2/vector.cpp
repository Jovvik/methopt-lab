#include "lab2/vector.h"

#include <cmath>
#include <utility>

using namespace lab2;

Vector::Vector(const std::vector<double>& data_) : data(data_) {
    if (size() == 0) {
        throw "Vector is empty";
    }
}

Vector::Vector(std::vector<double>&& data_) : data(data_) {
    if (size() == 0) {
        throw "Vector is empty";
    }
}

Vector::Vector(std::size_t size,
               const std::function<double(std::size_t)>& generator) {
    data.reserve(size);
    for (std::size_t i = 0; i < size; i++) {
        data.push_back(generator(i));
    }
}

std::size_t Vector::size() const { return data.size(); }

double Vector::operator[](std::size_t idx) const { return data[idx]; }

double Vector::norm() const { return std::sqrt((*this) * (*this)); }

Vector Vector::operator+(Vector other) const {
    if (size() != other.size()) {
        throw "Size mismatch";
    }
    return Vector(size(), [this, &other](std::size_t i) {
        return (*this)[i] + other[i];
    });
}

Vector Vector::operator*(double val) const {
    std::vector<double> tmp;
    return Vector(size(), [this, val](std::size_t i) {
        return (*this)[i] * val;
    });
}

double Vector::operator*(const Vector& other) const {
    if (size() != other.size()) {
        throw "Size mismatch";
    }
    double res = 0;
    for (std::size_t i = 0; i < size(); i++) {
        res += (*this)[i] * other[i];
    }
    return res;
}

bool Vector::operator==(const Vector& other) const {
    return data == other.data;
}
