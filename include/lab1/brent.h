#pragma once

#include <cmath>

#include "lab1/optimizer.h"

namespace lab1 {
    /**
     * Оптимизатор на основе комбинированного метода Брента
     */
    class Brent : public Optimizer {
      public:
        Brent(const func& optimized_function, double epsilon, double start,
              double end);

      protected:
        void step();
        bool is_done();

      private:
        const double TAU = (3 - std::sqrt(5)) / 2;
        double d, e;
        double x, w, v;
        double fx, fw, fv;
        bool m_is_done = false;
    };
}  // namespace lab1
