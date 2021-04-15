#include "lab2/functions.h"

#include "lab2/matrix.h"
#include "lab2/vector.h"

using namespace lab2;

QuadraticFunction Functions::paraboloid = QuadraticFunction(
    new Matrix({{2, 0}, {0, 2}}, 2), Vector(std::vector<double>{0, 0}), 1);

QuadraticFunction Functions::f1
    = QuadraticFunction(new Matrix({{2, -1}, {-1, 2}}, 3), Vector({4, 3}), -1);
