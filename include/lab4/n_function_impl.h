#pragma once

#include <memory>
#include <vector>

#include "lab2/matrix.h"
#include "lab2/n_function.h"
#include "lab2/vector.h"

namespace lab4 {
    class NFunctionImpl : public lab2::NFunction {
      public:
        NFunctionImpl(std::size_t dim, std::function<double(lab2::Vector)> f,
                      std::function<lab2::Vector(lab2::Vector)> grad_f,
                      std::function<lab2::Matrix(lab2::Vector)> hessian_f);

        double operator()(lab2::Vector x) override;
        lab2::Vector grad(lab2::Vector x) override;
        std::size_t get_dim() override;
        lab2::Matrix hessian(lab2::Vector x) override;

      private:
        const std::size_t dim;
        const std::function<double(lab2::Vector)> f;
        const std::function<lab2::Vector(lab2::Vector)> grad_f;
        const std::function<lab2::Matrix(lab2::Vector)> hessian_f;
    };
}  // namespace lab4
