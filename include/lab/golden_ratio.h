#pragma once

#include <cmath>

#include "lab/two_point.h"

namespace lab {
    /**
     * Оптимизатор на основе метода золтого сечения
     */
    class GoldenRatio : public TwoPoint {
      public:
        GoldenRatio(const func& optimized_function, double epsilon,
                    double start, double end);

      protected:
        void step();

      protected:
        double get_x1(double start, double end);
        double get_x2(double start, double end);

      private:
        const double TAU = (std::sqrt(5) - 1) / 2;
    };

}  // namespace lab
