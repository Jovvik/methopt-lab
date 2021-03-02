#pragma once

#include <cmath>

#include "lab/two_point.h"

namespace lab {
    /**
     * Оптимизатор на основе метода золтого сечения
     */
    class GoldenRatio : public TwoPoint {
      protected:
        Segment step(Segment current_segment, func optimized_function);

      private:
        double get_x1(double start, double end);
        double get_x2(double start, double end);

        const double TAU = (std::sqrt(5) - 1) / 2;
    };

}  // namespace lab
