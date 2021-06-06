#pragma once

#include "lab2/n_optimizer.h"
#include "lab2/matrix.h"

namespace lab4 {
    class DFP : public lab2::NOptimizer {
      public:
        DFP();

        lab2::Vector iteration(lab2::NFunction& f, double epsilon) override;
        bool is_done(lab2::NFunction& f, double epsilon) const override;

      private:
        lab2::Vector w, p, delta_x;
        lab2::Matrix *G{};
        const double ONE_DIM_EPS = 1e-7;
        const int ONE_DIM_START = -100, ONE_DIM_END = 100;
    };
}  // namespace lab4
