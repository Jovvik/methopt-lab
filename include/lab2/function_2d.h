#pragma once

#include "functions.h"
#include "lab2/n_function.h"
#include "lab2/quadratic_function.h"

namespace lab2 {
    class Function2D : public NFunction {
      public:
        explicit Function2D(QuadraticFunction *f_2d);
        [[nodiscard]] std::pair<double, double> get_y(double x, double z) const;
        double operator()(double x, double y);
        double operator()(Vector x) override;
        Vector grad(Vector x) override;
        QuadraticFunction *f;
        std::size_t get_dim() override;
    };
}  // namespace lab2
