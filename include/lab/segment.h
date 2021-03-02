#pragma once

#include <optional>
#include <utility>
#include <vector>

namespace lab {
    /**
     * Отрезок [`start`, `end`] и последовательность точек, используемых при
     * работе оптимизатора, а также значения f на этих точках.
     */
    class Segment {
      public:
        Segment(double start, double end);
        Segment(double start, double end,
                std::vector<std::pair<double, double>> points);

        double get_start();
        double get_end();
        std::optional<double> get_ans();
        const std::vector<std::pair<double, double>>& get_points();

        void set_ans(double ans);

      private:
        double start, end;
        std::optional<double> ans;
        std::vector<std::pair<double, double>> points;
    };
}  // namespace lab
