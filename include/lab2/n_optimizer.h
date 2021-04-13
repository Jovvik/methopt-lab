#pragma once

#include "lab2/n_function.h"
#include "lab2/vector.h"

namespace lab2 {

    class NOptimizer {
      public:
        Vector optimize(NFunction& f, const Vector& starting_point,
                        double epsilon);
        [[nodiscard]] const std::vector<Vector>& get_points() const;

      protected:
        [[nodiscard]] bool is_done(NFunction& f, double epsilon) const;
        [[nodiscard]] virtual Vector step(const NFunction& f) const = 0;

      private:
        std::vector<Vector> points;
    };

}  // namespace lab2
