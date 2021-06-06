#pragma once

#include "lab2/n_optimizer.h"

namespace lab4 {
    class ClassicNewton : public lab2::NOptimizer {
      public:
        ClassicNewton();

        lab2::Vector iteration(lab2::NFunction& f, double epsilon) override;
        bool is_done(lab2::NFunction& f, double epsilon) const override;

      private:
        lab2::Vector p;
    };
}  // namespace lab4
