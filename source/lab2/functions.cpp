#include <cmath>
#include "lab2/functions.h"

#include "lab2/matrix.h"
#include "lab2/vector.h"

using namespace lab2;

QuadraticFunction Functions::paraboloid = QuadraticFunction(
    new Matrix({{2, 0}, {0, 2}}, 2), Vector(std::vector<double>{0, 0}), 1);

QuadraticFunction Functions::f1
    = QuadraticFunction(new Matrix({{2, -1}, {-1, 2}}, 3), Vector({4, 3}), -1);

QuadraticFunction Functions::f2
        = QuadraticFunction(new Matrix({{508, 506}, {506, 508}}),
                            Vector({50, 130}), -111);

QuadraticFunction Functions::f3
        = QuadraticFunction(new Matrix({{216, 80}, {80, 232}}, 8*(28 + sqrt(101))),
                            Vector({43, 33}), -211);