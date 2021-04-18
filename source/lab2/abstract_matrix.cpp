#include "lab2/abstract_matrix.h"

using namespace lab2;

AbstractMatrix::AbstractMatrix(std::optional<double> max_eigenvalue)
    : max_eigenvalue(max_eigenvalue) {}
