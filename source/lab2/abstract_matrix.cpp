#include "lab2/abstract_matrix.h"

using namespace lab2;

AbstractMatrix::AbstractMatrix(std::optional<double> max_eigenvalue)
    : has_max_eigenvalue(max_eigenvalue.has_value()) {
    if (has_max_eigenvalue) {
        this->max_eigenvalue_ = *max_eigenvalue;
    }
}
double AbstractMatrix::max_eigenvalue() const {
    if (!has_max_eigenvalue) {
        throw "No eigenvalue";
    }
    return max_eigenvalue_;
}
