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

QuadraticFunction Functions::f_1_2_1 = QuadraticFunction(
    new Matrix({{2, -1.2}, {-1.2, 2}}, 1), Vector({0.0, 0.0}), 0);

lab4::NFunctionImpl Functions::f_2_1 = lab4::NFunctionImpl(
    2,
    [](Vector v) {
        double x = v[0];
        double y = v[1];
        return 100 * (y - x * x) * (y - x * x) + (1 - x) * (1 - x);
    },
    [](Vector v) {
        double x = v[0];
        double y = v[1];
        return Vector(
            {2 * (-1 + x + 200 * x * x * x - 200 * x * y), 200 * (-x * x + y)});
    },
    [](Vector v) {
        double x = v[0];
        double y = v[1];
        return Matrix({{-400 * (y - x * x) + 800 * x * x + 2, -400 * x},
                       {-400 * x, 200}});
    });

lab4::NFunctionImpl Functions::f_2_2 = lab4::NFunctionImpl(
    2,
    [](Vector v) {
        double x = v[0];
        double y = v[1];
        return (x * x + y - 11) * (x * x + y - 11)
               + (x + y * y - 7) * (x + y * y - 7);
    },
    [](Vector v) {
        double x = v[0];
        double y = v[1];
        return Vector({2 * (-7 + x + y * y + 2 * x * (-11 + x * x + y)),
                       2 * (-11 + x * x + y + 2 * y * (-7 + x + y * y))});
    },
    [](Vector v) {
        double x = v[0];
        double y = v[1];
        return Matrix({{2 + 8 * x * x + 4 * (-11 + x * x + y), 4 * x + 4 * y},
                       {4 * x + 4 * y, 2 + 8 * y * y + 4 * (-7 + x + y * y)}});
    });

lab4::NFunctionImpl Functions::f_2_3 = lab4::NFunctionImpl(
    4,
    [](Vector v) {
        return std::pow(v[0] + 10 * v[1] * v[1], 2)
               + 5 * std::pow(v[2] - v[3], 2) + std::pow(v[1] - 2 * v[2], 4)
               + 10 * std::pow(v[0] - v[3], 4);
    },
    [](Vector v) {
        double x = v[0];
        double y = v[1];
        double z = v[2];
        double k = v[3];
        return Vector({2 * (x + 10 * y + 20 * std::pow(x - z, 3)),
                       4 * (5 * (x + 10 * y) + std::pow(y - 2 * z, 3)),
                       -8 * std::pow(y - 2 * z, 3) - 40 * std::pow(x - z, 3)
                           + 10 * (-k + z),
                       -10 * (-k + z)});
    },
    [](Vector v) {
        double x = v[0];
        double y = v[1];
        double z = v[2];
        double k = v[3];
        return Matrix(
            {{2 + 120 * (x - k) * (x - k), 20, 0, -120 * (x - k) * (x - k)},
             {20, 200 + 12 * (y - 2 * z) * (y - 2 * z),
              -24 * (y - 2 * z) * (y - 2 * z), 0},
             {0, -24 * (y - 2 * z) * (y - 2 * z),
              10 + 48 * (y - 2 * z) * (y - 2 * z), -10},
             {-120 * (x - k) * (x - k), 0, -10, 10 + 120 * (x - k) * (x - k)}});
    });

lab4::NFunctionImpl Functions::f_2_4 = lab4::NFunctionImpl(
    2,
    [](Vector v) {
        double x = v[0];
        double y = v[1];
        return 100
               - 2 / (1 + std::pow((x - 1) / 2, 2) + std::pow((y - 1) / 3, 2))
               - 1 / (1 + std::pow((x - 2) / 2, 2) + std::pow((y - 1) / 8, 2));
    },
    [](Vector v) {
        double x = v[0];
        double y = v[1];
        return Vector({(-2 + x)
                               / (2
                                  * std::pow(1 + std::pow(-2 + x, 2) / 4
                                                 + std::pow(-1 + y, 2) / 9,
                                             2))
                           + (-1 + x)
                                 / std::pow(1 + std::pow(-1 + x, 2) / 4
                                                + std::pow(-1 + y, 2) / 9,
                                            2),
                       (2 * (-1 + y))
                               / (9
                                  * std::pow(1 + std::pow(-2 + x, 2) / 4
                                                 + std::pow(-1 + y, 2) / 9,
                                             2))
                           + (4 * (-1 + y))
                                 / (9
                                    * std::pow(1 + std::pow(-1 + x, 2) / 4
                                                   + std::pow(-1 + y, 2) / 9,
                                               2))});
    },
    [](Vector v) {
        double x = v[0];
        double y = v[1];
        return Matrix(
            {{-2
                      * (std::pow(-1 + x, 2)
                             / (2
                                * std::pow(1 + std::pow(-1 + x, 2) / 4
                                               + std::pow(-1 + y, 2) / 9,
                                           3))
                         - 1
                               / (2
                                  * std::pow(1 + std::pow(-1 + x, 2) / 4
                                                 + std::pow(-1 + y, 2) / 9,
                                             2)))
                  - std::pow(-2 + x, 2)
                        / (2
                           * std::pow(1 + std::pow(-2 + x, 2) / 4
                                          + std::pow(-1 + y, 2) / 9,
                                      3))
                  + 1
                        / (2
                           * std::pow(1 + std::pow(-2 + x, 2) / 4
                                          + std::pow(-1 + y, 2) / 9,
                                      2)),
              (-2 * (-2 + x) * (-1 + y))
                      / (9
                         * std::pow(1 + std::pow(-2 + x, 2) / 4
                                        + std::pow(-1 + y, 2) / 9,
                                    3))
                  - (4 * (-1 + x) * (-1 + y))
                        / (9
                           * std::pow(1 + std::pow(-1 + x, 2) / 4
                                          + std::pow(-1 + y, 2) / 9,
                                      3))},
             {(-2 * (-2 + x) * (-1 + y))
                      / (9
                         * std::pow(1 + std::pow(-2 + x, 2) / 4
                                        + std::pow(-1 + y, 2) / 9,
                                    3))
                  - (4 * (-1 + x) * (-1 + y))
                        / (9
                           * std::pow(1 + std::pow(-1 + x, 2) / 4
                                          + std::pow(-1 + y, 2) / 9,
                                      3)),
              2
                      / (9
                         * std::pow(1 + std::pow(-2 + x, 2) / 4
                                        + std::pow(-1 + y, 2) / 9,
                                    2))
                  - 2
                        * (-2
                               / (9
                                  * std::pow(1 + std::pow(-1 + x, 2) / 4
                                                 + std::pow(-1 + y, 2) / 9,
                                             2))
                           + (8 * std::pow(-1 + y, 2))
                                 / (81
                                    * std::pow(1 + std::pow(-1 + x, 2) / 4
                                                   + std::pow(-1 + y, 2) / 9,
                                               3)))
                  - (8 * std::pow(-1 + y, 2))
                        / (81
                           * std::pow(1 + std::pow(-2 + x, 2) / 4
                                          + std::pow(-1 + y, 2) / 9,
                                      3))}});
    });