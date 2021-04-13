#pragma once

#include "lab2/n_optimizer.h"

namespace lab2 {
    class GradientDescent : public NOptimizer {
      public:
        explicit GradientDescent(double step) : a(step) {}
        Vector iteration(NFunction &f) override;

      private:
        [[nodiscard]] Vector points_last() const;
        double a;
    };
}  // namespace lab2
