#pragma once

#include "functions.h"
#include "lab2/n_function.h"
#include "lab2/quadratic_function.h"

namespace lab2 {
    class Function2D {
      public:
        explicit Function2D(QuadraticFunction *f_2d);
        std::pair<double, double> get_y(double x, double z);
        double operator()(double x, double y);
        QuadraticFunction *f;
    };
}  // namespace lab2
