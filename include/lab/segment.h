#pragma once

#include <ostream>
#include <utility>
#include <vector>

namespace lab {
    /**
     * Отрезок [`start`, `end`] и последовательность точек, используемых при
     * работе оптимизатора, а также значения f на этих точках.
     */
    class Segment {
      public:
        double start, end;
        std::vector<std::pair<double, double>> points;
        Segment(double start, double end);
        Segment(double start, double end,
                std::vector<std::pair<double, double>> points);
    };
}  // namespace lab
