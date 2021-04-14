#pragma once

#include "lab2/n_function.h"
#include "lab2/quadratic_function.h"

namespace lab2 {
    class Functions {
      public:
        Functions() = delete;

        /**
         * Параболоид x^2 + y^2 + 1
         */
        static QuadraticFunction paraboloid();
        /**
         * x^2 + y^2 - xy + 4x + 3y - 1
         */
        static QuadraticFunction f1();
    };
}  // namespace lab2
