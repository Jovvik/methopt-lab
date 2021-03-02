#pragma once

#include "lab/golden_ratio.h"

namespace lab {
    class Fibonacci : public GoldenRatio {
      public:
        double optimize(func optimized_function, double epsilon, double start,
                        double end);

      protected:
        bool is_done(Segment current_segment, double epsilon);

      private:
        double get_x1(double start, double end);
        double get_x2(double start, double end);
        /**
         * @return n-тое число Фибоначчи
         */
        double fib(int n);

        /**
         * Начальная левая граница
         */
        double initial_start;
        /**
         * Начальная правая граница
         */
        double initial_end;

        /**
         * Число для получения ответа
         */
        int n;
    };
}  // namespace lab
