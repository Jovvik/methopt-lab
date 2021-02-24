#pragma once

#include <ostream>
#include <utility>
#include <vector>

namespace lab {

    class Segment {
      public:
        const double start, end;
        const std::vector<std::pair<double, double>> points;

        Segment(double start, double end, std::vector<std::pair<double, double>> points);
    };
}  // namespace lab
