#pragma once

#include <memory>

#include "lab2/matrix.h"
#include "lab2/n_function.h"
#include "lab2/vector.h"

namespace lab2 {
    /**
     * Квадратичная функция вида f(x) = <A x, x> + <b, x> + c, где
     * <> обозначает векторное произведение
     */
    class QuadraticFunction : public NFunction {
      public:
        QuadraticFunction(AbstractMatrix* A, Vector&& b, double c);
        double operator()(Vector x) override;
        Vector grad(Vector x) override;
        std::size_t get_dim() override;
        Matrix hessian(Vector x) override;

        std::unique_ptr<AbstractMatrix> A;
        const Vector b;
        const double c;
    };
}  // namespace lab2
