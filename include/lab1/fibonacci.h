#pragma once

#include "lab1/golden_ratio.h"

namespace lab1 {
    class Fibonacci : public GoldenRatio {
      public:
        Fibonacci(const func& optimized_function, double epsilon, double start,
                  double end);

      protected:
        bool is_done();

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
         * Число итераций для получения ответа
         */
        int n;
    };
}  // namespace lab1
