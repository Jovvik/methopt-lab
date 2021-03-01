#pragma once

#include <cmath>

#include "lab/dichotomy.h"
#include "lab/two_point.h"

namespace lab {
    /**
     * Оптимизатор на основе метода золтого сечения
     */
    class GoldenRatio : public TwoPoint {
      protected:
        Segment step(Segment current_segment, func optimized_function);

      private:
        /**
         * Вычисляет x_1
         */
        double get_x1(double start, double end);

        /**
         * Вычисляет x_2
         */
        double get_x2(double start, double end);

        const double TAU = (std::sqrt(5) - 1) / 2;
    };

}  // namespace lab
