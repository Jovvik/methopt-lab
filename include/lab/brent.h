#pragma once

#include <cmath>

#include "lab/optimizer.h"

namespace lab {
    /**
     * Оптимизатор на основе комбинированного метода Брента
     */
    class Brent : public Optimizer {
      public:
        Brent(const func& optimized_function, double epsilon, double start,
              double end);

      protected:
        void step();

      private:
        const double TAU = (3 - std::sqrt(5)) / 2;
        double d, e, g;
        double x, w, v;
        double fx, fw, fv;

        bool areDistinct(double a, double b, double c) {
            return a != b && b != c;
        }

        double parabola(double start, double mid, double end, double f_start,
                        double f_mid, double f_end) {
            return mid
                   - 0.5
                         * ((mid - start) * (mid - start) * (f_mid - f_end)
                            - (mid - end) * (mid - end) * (f_mid - f_start))
                         / ((mid - start) * (f_mid - f_end)
                            - (mid - end) * (f_mid - f_start));
        }
    };
}  // namespace lab
