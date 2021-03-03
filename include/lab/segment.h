#pragma once

#include <optional>
#include <utility>
#include <vector>

namespace lab {
    /**
     * Отрезок [`start`, `end`]
     * (возможно) ответ `ans` для данного отрезка
     * (возможно) точка `mid`, по которой проходит аппроксимирующая парабола
     */
    class Segment {
      public:
        Segment(double start, double end);
        Segment(double start, double mid, double end);

        double get_start();
        double get_end();
        std::optional<double> get_ans();
        std::optional<double> get_mid();

        void set_ans(double ans);
        void set_mid(double mid);

      private:
        double start;
        std::optional<double> mid;
        double end;
        std::optional<double> ans;
    };
}  // namespace lab
