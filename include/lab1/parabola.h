#pragma once

#include "lab1/optimizer.h"

namespace lab1 {
    /**
     * Оптимизатор на основе метода парабол
     */
    class Parabola : public Optimizer {
      public:
        Parabola(const func& optimized_function, double epsilon, double start,
                 double end);

      protected:
        void step();
        double answer();

      private:
        double f_start, f_mid, f_end;
    };
}  // namespace lab1
