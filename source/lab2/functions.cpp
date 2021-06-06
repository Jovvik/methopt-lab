#include "lab2/functions.h"

#include <cmath>

#include "lab2/matrix.h"
#include "lab2/vector.h"

using namespace lab2;

QuadraticFunction Functions::paraboloid = QuadraticFunction(
    new Matrix({{2, 0}, {0, 2}}, 2), Vector(std::vector<double>{0, 0}), 1);

QuadraticFunction Functions::f1
    = QuadraticFunction(new Matrix({{2, -1}, {-1, 2}}, 3), Vector({4, 3}), -1);

QuadraticFunction Functions::f2 = QuadraticFunction(
    new Matrix({{508, 506}, {506, 508}}), Vector({50, 130}), -111);

QuadraticFunction Functions::f3 = QuadraticFunction(
    new Matrix({{216, 80}, {80, 232}}, 8 * (28 + sqrt(101))), Vector({43, 33}),
    -211);

lab4::NFunctionImpl Functions::sincos = lab4::NFunctionImpl(
    2,
    [](Vector v) {
        double x = v[0];
        double y = v[1];
        return sin(x) + cos(y) + 0.3 * y * y + 0.3 * x * x + y * 0.1;
    },
    [](Vector v) {
        double x = v[0];
        double y = v[1];
        return Vector({0.6 * x + cos(x), 0.6 * y - sin(y) + 0.1});
    },
    [](Vector v) {
        double x = v[0];
        double y = v[1];
        return Matrix({{0.6 - sin(x), 0}, {0, 0.6 - cos(y)}});
    });