#pragma once

#include "lab1/optimizer.h"
#include "lab1/two_point.h"

namespace lab1 {
    /**
     * Оптимизатор на основе метода дихотомии
     */
    class Dichotomy : public TwoPoint {
        using TwoPoint::TwoPoint;

      protected:
        void step();
        double get_x1(double start, double end);
        double get_x2(double start, double end);

      private:
        double delta = epsilon / 2;
    };

}  // namespace lab1
