#include "lab/vector.h"

#include <assert.h>

#include <numeric>

using namespace lab;

Vector::Vector(const std::vector<double>& data_) : data(data_) {}

Vector::Vector(std::vector<double>&& data_) : data(data_) {}

std::size_t Vector::size() const { return data.size(); }

double Vector::operator[](std::size_t idx) const { return data[idx]; }

Vector Vector::operator+(Vector other) const {
    assert(size() == other.size());
    std::vector<double> tmp;
    tmp.reserve(size());
    for (std::size_t i = 0; i < size(); i++) {
        tmp.push_back((*this)[i] + other[i]);
    }
    return Vector(std::move(tmp));
}

double Vector::operator*(Vector other) const {
    assert(size() == other.size());
    double res = 0;
    for (std::size_t i = 0; i < size(); i++) {
        res += (*this)[i] * other[i];
    }
    return res;
}

Vector Vector::operator*(double val) const {
    std::vector<double> tmp;
    tmp.reserve(size());
    for (std::size_t i = 0; i < size(); i++) {
        tmp.push_back((*this)[i] * val);
    }
    return Vector(std::move(tmp));
}
