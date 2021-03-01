#pragma once

#include <cmath>

#include "lab/optimizer.h"

namespace lab {
    /**
     * Общий класс оптимизаторов, которые на каждом шаге рассматривают две точки
     */
    class TwoPoint : public Optimizer {
      protected:
        bool is_done(Segment current_segment, double epsilon);
        double answer(Segment current_segment);
        Segment new_segment(Segment current_segment, func optimized_function);

      private:
        /**
         * Вычисляет первую точку для рассмотрения
         */
        virtual double get_x1(double start, double end) = 0;

        /**
         * Вычисляет вторую точку для рассмотрения
         */
        virtual double get_x2(double start, double end) = 0;
    };

}  // namespace lab