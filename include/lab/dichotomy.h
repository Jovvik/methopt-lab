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
        bool is_done(Segment current_segment, double epsilon);
        Segment step(Segment current_segment, func optimized_function);
        double answer(Segment current_segment);
        Segment new_segment(Segment current_segment, func optimized_function);

      private:
        /**
         * Вычисляет x_1
         */
        double get_x1(double start, double end);

        /**
         * Вычисляет x_2
         */
        double get_x2(double start, double end);

        double delta;
    };

}  // namespace lab