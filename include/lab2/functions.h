#pragma once

#include "lab2/n_function.h"
#include "lab2/quadratic_function.h"
#include "lab4/n_function_impl.h"

namespace lab2 {
    class Functions {
      public:
        Functions() = delete;

        /**
         * Параболоид x^2 + y^2 + 1
         */
        static QuadraticFunction paraboloid;
        /**
         * x^2 + y^2 - xy + 4x + 3y - 1
         */
        static QuadraticFunction f1;

        /**
         * 254x^2 + 506xy + 254y^2 + 50x + 130y - 111
         */
        static QuadraticFunction f2;

        /**
         * 108x^2 + 116y^2 + 80xy + 43x + 33y - 211
         */
        static QuadraticFunction f3;

        static lab4::NFunctionImpl sincos;

        static QuadraticFunction f_1_2_1;
        static lab4::NFunctionImpl f_2_1;
        static lab4::NFunctionImpl f_2_2;
        static lab4::NFunctionImpl f_2_3;
        static lab4::NFunctionImpl f_2_4;
    };

    static std::unordered_map<std::string, QuadraticFunction*> const
        functions_table
        = {{"x^2 + y^2 + 1", &Functions::paraboloid},
           {"x^2 + y^2 - xy + 4x + 3y - 1", &Functions::f1},
           {"254x^2 + 506xy + 254y^2 + 50x + 130y - 111", &Functions::f2},
           {"108x^2 + 116y^2 + 80xy + 43x + 33y - 211", &Functions::f3}};
}  // namespace lab2
