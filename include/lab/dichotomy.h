#pragma once

#include "lab/optimizer.h"
#include "lab/two_point.h"

namespace lab {
    /**
     * Оптимизатор на основе метода дихотомии
     */
    class Dichotomy : public TwoPoint {
      public:
        explicit Dichotomy(double delta);

      protected:
        Segment step(Segment current_segment, func optimized_function);

      private:
        double get_x1(double start, double end);
        double get_x2(double start, double end);

        double delta;
    };

}  // namespace lab